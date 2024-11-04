#ifndef CUDACOREINCLUDELIBS_H
#define CUDACOREINCLUDELIBS_H

#include "Renderer_OpenGL/Includes/IncludeLibs.h"


#ifdef _WIN64 // x64
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Common/bin/Common_x64_Debug.lib")
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x64_Debug.lib")
#else
#pragma comment(lib, "../Libs/Common/bin/Common_x64_Release.lib")
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x64_Release.lib")
#endif
#else // (x86)
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x86_Debug.lib")
#pragma comment(lib, "../Libs/Common/bin/Common_x86_Debug.lib")
#else
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x86_Release.lib")
#pragma comment(lib, "../Libs/Common/bin/Common_x86_Release.lib")
#endif
#endif


#include "Common/Includes/pch.h"
#include "Renderer_OpenGL/Includes/pch.h"

#endif