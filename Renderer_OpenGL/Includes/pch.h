// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef RendererOPENGLPCH_H
#define RendererOPENGLPCH_H

// add headers that you want to pre-compile here
#include "framework.h"

// Renderer Common
#include "Renderer_Common/Includes/pch.h"
#include "Renderer_Common/Includes/Macros.h"

// OpenGL
//#pragma comment(lib, "../Libs/GLFW/glfw3.lib")
#include "Libs/glad/glad.h"
#include "Libs/GLFW/glfw3.h"
#include "Libs/glm/glm.hpp"


// My
#include "Renderer_OpenGL/Includes/Macros.h"
#include "Renderer_OpenGL/Includes/Typedefs.h"

// My
#include "Renderer_OpenGL/Includes/Macros.h"

//#pragma comment(lib, "Renderer_Common_x64_Debug.lib")
#endif //RendererOPENGLPCH_H
