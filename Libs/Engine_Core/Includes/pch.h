// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef ENGINECORE_PCH_H
#define ENGINECORE_PCH_H

// Linking
#include "IncludeLibs.h"

//#include "Common/Includes/pch.h"
//#include "Renderer_OpenGL/Includes/pch.h"


// Math Lib : Engine Core Uses SimpleMath(Vector3), Renderer Uses DirectXMath(FLOAT3)
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

// Engine Core
extern class CInputManager* g_Input;

#endif //ENGINECORE_PCH_H
