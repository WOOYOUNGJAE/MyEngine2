#pragma once

#include "Renderer_OpenGL/Includes/Linking.h"


#ifdef _WIN64 // x64
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x64_Debug.lib")
#else
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x64_Release.lib")
#endif
#else // (x86)
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x86_Debug.lib")
#else
#pragma comment(lib, "../Libs/Renderer_OpenGL/bin/Renderer_OpenGL_x86_Release.lib")
#endif
#endif
