// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef ENGINEOPENGLPCH_H
#define ENGINEOPENGLPCH_H

// add headers that you want to pre-compile here
#include "framework.h"

// Engine Common
#include "Engine_Common/pch.h"
#include "Engine_Common/Headers/Macros.h"

// OpenGL
#pragma comment(lib, "glfw3.lib")
#include "Extlibs/glad/glad/glad.h"
#include "glfw3.h"
#include "Extlibs/glm/glm.hpp"


// My
#include "Engine_OpenGL/Headers/Macros.h"
#include "Engine_OpenGL/Headers/Typedefs.h"

// My
#include "Engine_OpenGL/Headers/Macros.h"

#pragma comment(lib, "Engine_Common.lib")
#endif //ENGINEOPENGLPCH_H
