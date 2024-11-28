/*

 * SPDX-FileCopyrightText: Copyright (c) 2019 - 2024  NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "sutil.h"
#include "OptixException.h"
#include <GLFW/glfw3.h>

#include <nvrtc.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <vector>
#if defined(_WIN32)
#    ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN 1
#    endif
#    include<windows.h>
#    include<mmsystem.h>
#else
#    include<sys/time.h>
#    include <unistd.h>
#    include <dirent.h>
#endif


namespace sutil
{

static void errorCallback( int error, const char* description )
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}


static void keyCallback( GLFWwindow* window, int32_t key, int32_t /*scancode*/, int32_t action, int32_t /*mods*/ )
{
    if( action == GLFW_PRESS )
    {
        if( key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE )
        {
            glfwSetWindowShouldClose( window, true );
        }
    }
}

static bool dirExists( const char* path )
{
#if defined( _WIN32 )
    DWORD attrib = GetFileAttributes( path );
    return ( attrib != INVALID_FILE_ATTRIBUTES ) && ( attrib & FILE_ATTRIBUTE_DIRECTORY );
#else
    DIR* dir = opendir( path );
    if( dir == NULL )
        return false;

    closedir( dir );
    return true;
#endif
}

static bool fileExists( const char* path )
{
    std::ifstream str( path );
    return static_cast<bool>( str );
}

static bool fileExists( const std::string& path )
{
    return fileExists( path.c_str() );
}

static std::string existingFilePath( const char* directory, const char* relativeSubDir, const char* relativePath )
{
    std::string path = directory ? directory : "";
    if( relativeSubDir )
    {
        path += '/';
        path += relativeSubDir;
    }
    if( relativePath )
    {
        path += '/';
        path += relativePath;
    }
    return fileExists( path ) ? path : "";
}

static bool readSourceFile( std::string& str, const std::string& filename )
{
    // Try to open file
    std::ifstream file( filename.c_str(), std::ios::binary );
    if( file.good() )
    {
        // Found usable source file
        std::vector<unsigned char> buffer = std::vector<unsigned char>( std::istreambuf_iterator<char>( file ), {} );
        str.assign(buffer.begin(), buffer.end());
        return true;
    }
    return false;
}

// Returns string of file extension including '.'
static std::string fileExtensionForLoading()
{
    std::string extension;
#if SAMPLES_INPUT_GENERATE_PTX
    extension = ".ptx";
#endif
#if SAMPLES_INPUT_GENERATE_OPTIXIR
    extension = ".optixir";
#endif
    if( const char* ext = getenv("OPTIX_SAMPLES_INPUT_EXTENSION") )
    {
        extension = ext;
        if( extension.size() && extension[0] != '.' )
            extension = "." + extension;
    }
    return extension;
}

#if CUDA_NVRTC_ENABLED

static void getCuStringFromFile( std::string& cu, std::string& location, const char* sampleDir, const char* filename )
{
    std::vector<std::string> source_locations;

    const std::string base_dir = getSampleDir();

    // Potential source locations (in priority order)
    if( sampleDir )
        source_locations.push_back( base_dir + '/' + sampleDir + '/' + filename );
    source_locations.push_back( base_dir + "/cuda/" + filename );

    for( const std::string& loc : source_locations )
    {
        // Try to get source code from file
        if( readSourceFile( cu, loc ) )
        {
            location = loc;
            return;
        }
    }

    // Wasn't able to find or open the requested file
    throw std::runtime_error( "Couldn't open source file " + std::string( filename ) );
}

static std::string g_nvrtcLog;

static void getInputFromCuString( std::string&                    input,
                                  const char*                     sample_directory,
                                  const char*                     cu_source,
                                  const char*                     name,
                                  const char**                    log_string,
                                  const std::vector<const char*>& compiler_options )
{
    // Create program
    nvrtcProgram prog = 0;
    NVRTC_CHECK_ERROR( nvrtcCreateProgram( &prog, cu_source, name, 0, NULL, NULL ) );

    // Gather NVRTC options
    std::vector<const char*> options;

    const std::string base_dir = getSampleDir();

    // Set sample dir as the primary include path
    std::string sample_dir;
    if( sample_directory )
    {
        sample_dir = std::string( "-I" ) + base_dir + '/' + sample_directory;
        options.push_back( sample_dir.c_str() );
    }

    // Collect include dirs
    std::vector<std::string> include_dirs;
    const char*              abs_dirs[] = {SAMPLES_ABSOLUTE_INCLUDE_DIRS};
    const char*              rel_dirs[] = {SAMPLES_RELATIVE_INCLUDE_DIRS};

    for( const char* dir : abs_dirs )
    {
        include_dirs.push_back( std::string( "-I" ) + dir );
    }
    for( const char* dir : rel_dirs )
    {
        include_dirs.push_back( "-I" + base_dir + '/' + dir );
    }
    for( const std::string& dir : include_dirs)
    {
        options.push_back( dir.c_str() );
    }

    bool optixir = fileExtensionForLoading() == ".optixir";
    if( optixir )
        options.push_back( "--optix-ir" );

    // Collect NVRTC options
    std::copy( std::begin( compiler_options ), std::end( compiler_options ), std::back_inserter( options ) );

    // JIT compile CU to OPTIXIR/PTX
    const nvrtcResult compileRes = nvrtcCompileProgram( prog, (int)options.size(), options.data() );

    // Retrieve log output
    size_t log_size = 0;
    NVRTC_CHECK_ERROR( nvrtcGetProgramLogSize( prog, &log_size ) );
    g_nvrtcLog.resize( log_size );
    if( log_size > 1 )
    {
        NVRTC_CHECK_ERROR( nvrtcGetProgramLog( prog, &g_nvrtcLog[0] ) );
        if( log_string )
            *log_string = g_nvrtcLog.c_str();
    }
    if( compileRes != NVRTC_SUCCESS )
        throw std::runtime_error( "NVRTC Compilation failed.\n" + g_nvrtcLog );

    // Retrieve OPTIXIR/PTX code
    size_t input_size = 0;
    if( optixir )
    {
#if CUDA_VERSION >= 12000
        NVRTC_CHECK_ERROR( nvrtcGetOptiXIRSize( prog, &input_size ) );
        input.resize( input_size );
        NVRTC_CHECK_ERROR( nvrtcGetOptiXIR( prog, &input[0] ) );
#else
        throw std::runtime_error( "OptiX IR support for NVRTC is only available with CUDA 12.0+" );
#endif
    }
    else
    {
        NVRTC_CHECK_ERROR( nvrtcGetPTXSize( prog, &input_size ) );
        input.resize( input_size );
        NVRTC_CHECK_ERROR( nvrtcGetPTX( prog, &input[0] ) );
    }

    // Cleanup
    NVRTC_CHECK_ERROR( nvrtcDestroyProgram( &prog ) );
}

#else  // CUDA_NVRTC_ENABLED

static std::string sampleInputFilePath( const char* sampleName, const char* fileName )
{
    // Allow for overrides.
    static const char* directories[] =
    {
        // TODO: Remove the environment variable OPTIX_EXP_SAMPLES_SDK_PTX_DIR once SDK 6/7 packages are split
        getenv( "OPTIX_EXP_SAMPLES_SDK_PTX_DIR" ),
        getenv( "OPTIX_SAMPLES_SDK_PTX_DIR" ),
 #if defined(CMAKE_INTDIR)
        SAMPLES_PTX_DIR "/" CMAKE_INTDIR,
#endif
        SAMPLES_PTX_DIR,
        "."
    };

    // Allow overriding the file extension
    std::string extension = fileExtensionForLoading();

    if( !sampleName )
        sampleName = "sutil";
    std::vector<std::string> locations;
    for( const char* directory : directories )
    {
        if( directory )
        {
            std::string path = directory;
            path += '/';
            path += sampleName;
            path += "_generated_";
            path += fileName;
            path += extension;
            locations.push_back( path );
            if( fileExists( path ) )
                return path;
        }
    }

    std::string error = "sutil::sampleInputFilePath couldn't locate " + std::string( fileName ) + " for sample "
                        + std::string( sampleName ) + " in the following locations:\n";
    for( const auto& path : locations )
        error += "\t" + path + "\n";

    throw Exception( error.c_str() );
}

static void getInputDataFromFile( std::string& inputData, const char* sample_name, const char* filename )
{
    const std::string sourceFilePath = sampleInputFilePath( sample_name, filename );

    // Try to open source file
    if( !readSourceFile( inputData, sourceFilePath ) )
    {
        std::string err = "Couldn't open source file " + sourceFilePath;
        throw std::runtime_error( err.c_str() );
    }
}

#endif  // CUDA_NVRTC_ENABLED

struct SourceCache
{
    std::map<std::string, std::string*> map;
    ~SourceCache()
    {
        for( std::map<std::string, std::string*>::const_iterator it = map.begin(); it != map.end(); ++it )
            delete it->second;
    }
};
static SourceCache g_sourceCache;

const char* getInputData( const char*                     sample,
                          const char*                     sampleDir,
                          const char*                     filename,
                          size_t&                         dataSize,
                          const char**                    log,
                          const std::vector<const char*>& compilerOptions )
{
    if( log )
        *log = NULL;

    std::string *                                 inputData, cu;
    std::string                                   key  = std::string( filename ) + ";" + ( sample ? sample : "" );
    std::map<std::string, std::string*>::iterator elem = g_sourceCache.map.find( key );

    if( elem == g_sourceCache.map.end() )
    {
        inputData = new std::string();
#if CUDA_NVRTC_ENABLED
        std::string location;
        getCuStringFromFile( cu, location, sampleDir, filename );
        getInputFromCuString( *inputData, sampleDir, cu.c_str(), location.c_str(), log, compilerOptions );
#else
        getInputDataFromFile( *inputData, sample, filename );
#endif
        g_sourceCache.map[key] = inputData;
    }
    else
    {
        inputData = elem->second;
    }
    dataSize = inputData->size();
    return inputData->c_str();
}

void ensureMinimumSize( int& w, int& h )
{
    if( w <= 0 )
        w = 1;
    if( h <= 0 )
        h = 1;
}

void ensureMinimumSize( unsigned& w, unsigned& h )
{
    if( w == 0 )
        w = 1;
    if( h == 0 )
        h = 1;
}

void reportErrorMessage( const char* message )
{
    std::cerr << "OptiX Error: '" << message << "'\n";
#if defined( _WIN32 ) && defined( RELEASE_PUBLIC )
    {
        char s[2048];
        sprintf( s, "OptiX Error: %s", message );
        MessageBoxA( 0, s, "OptiX Error", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL );
    }
#endif
}

} // namespace sutil
