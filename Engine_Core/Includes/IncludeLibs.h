#ifndef ENGINECOREINCLUDELIBS_H
#define ENGINECOREINCLUDELIBS_H

#include "Renderer_OpenGL/Includes/IncludeLibs.h"
#include "CUDA_Core/Includes/IncludeLibs.h"


#ifdef _WIN64 // x64
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x64_Debug.lib")
#pragma comment(lib, "../Libs/CUDA_Core/bin/CUDA_Core_x64_Debug.lib")
#else
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x64_Release.lib")
#pragma comment(lib, "../Libs/CUDA_Core/bin/CUDA_Core_x64_Release.lib")
#endif
#else // (x86)
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x86_Debug.lib")
#pragma comment(lib, "../Libs/CUDA_Core/bin/CUDA_Core_x86_Debug.lib")
#else
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x86_Release.lib")
#pragma comment(lib, "../Libs/CUDA_Core/bin/CUDA_Core_x86_Release.lib")
#endif
#endif


#endif
