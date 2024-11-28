#ifndef CUDACONFIG_H
#define CUDACONFIG_H


#ifdef CUDA_EXPORTS
#define CUDA_DLL _declspec(dllexport)
#else
#define CUDA_DLL _declspec(dllimport)
#endif


// Optix Config
#define SAMPLES_DIR "C:/ProgramData/NVIDIA Corporation/OptiX SDK 8.1.0/SDK"
#define SAMPLES_PTX_DIR "C:\\ProgramData\\NVIDIA Corporation\\OptiX SDK 8.1.0\\SDK\\build\\lib\\ptx"
#define SAMPLES_CUDA_DIR "C:/ProgramData/NVIDIA Corporation/OptiX SDK 8.1.0/SDK/cuda"

// Include directories
#define SAMPLES_RELATIVE_INCLUDE_DIRS \
  "cuda", \
  "sutil", \
  ".", 
#define SAMPLES_ABSOLUTE_INCLUDE_DIRS \
  "C:/ProgramData/NVIDIA Corporation/OptiX SDK 8.1.0/include", \
  "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8/include", 

// Signal whether to use NVRTC or not
#define CUDA_NVRTC_ENABLED 0

// NVRTC compiler options
#if defined( NDEBUG )
#define CUDA_NVRTC_OPTIONS  \
  "-std=c++11", \
  "-arch", \
  "compute_50", \
  "-lineinfo", \
  "-use_fast_math", \
  "-default-device", \
  "-rdc", \
  "true", \
  "-D__x86_64",
#else
#define CUDA_NVRTC_OPTIONS  \
  "-std=c++11", \
  "-arch", \
  "compute_50", \
  "-G", \
  "-use_fast_math", \
  "-default-device", \
  "-rdc", \
  "true", \
  "-D__x86_64",
#endif

// sutilApi
#ifndef SUTILAPI
#  if sutil_7_sdk_EXPORTS /* Set by CMAKE */
#    if defined( _WIN32 ) || defined( _WIN64 )
#      define SUTILAPI __declspec(dllexport)
#      define SUTILCLASSAPI
#    elif defined( linux ) || defined( __linux__ ) || defined ( __CYGWIN__ )
#      define SUTILAPI __attribute__ ((visibility ("default")))
#      define SUTILCLASSAPI SUTILAPI
#    elif defined( __APPLE__ ) && defined( __MACH__ )
#      define SUTILAPI __attribute__ ((visibility ("default")))
#      define SUTILCLASSAPI SUTILAPI
#    else
#      error "CODE FOR THIS OS HAS NOT YET BEEN DEFINED"
#    endif

#  else /* sutil_7_sdk_EXPORTS */

#    if defined( _WIN32 ) || defined( _WIN64 )
#      define SUTILAPI __declspec(dllimport)
#      define SUTILCLASSAPI
#    elif defined( linux ) || defined( __linux__ ) || defined ( __CYGWIN__ )
#      define SUTILAPI __attribute__ ((visibility ("default")))
#      define SUTILCLASSAPI SUTILAPI
#    elif defined( __APPLE__ ) && defined( __MACH__ )
#      define SUTILAPI __attribute__ ((visibility ("default")))
#      define SUTILCLASSAPI SUTILAPI
#    elif defined( __CUDACC_RTC__ )
#      define SUTILAPI
#      define SUTILCLASSAPI
#    else
#      error "CODE FOR THIS OS HAS NOT YET BEEN DEFINED"
#    endif

#  endif /* sutil_7_sdk_EXPORTS */
#endif


#endif