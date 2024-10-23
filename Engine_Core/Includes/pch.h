// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef ENGINECORE_PCH_H
#define ENGINECORE_PCH_H

#include "Renderer_Common/Includes/pch.h"
#include "Renderer_OpenGL/Includes/pch.h"

// add headers that you want to pre-compile here
#include "framework.h"



#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#include <iostream>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <initguid.h>

#include <combaseapi.h>


// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// STL
#include <vector>
#include <list>
using std::vector;
using std::list;


// DirectX for Common
#include <VertexTypes.h>
//#include <DirectXColors.h>
#include <DirectXMath.h>
//#include <SimpleMath.h>
using namespace DirectX;


// Math Lib : Engine Core Uses SimpleMath(Vector3), Renderer Uses DirectXMath(FLOAT3)
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

// Engine Core
extern class CInputManager* g_Input;

#endif //ENGINECORE_PCH_H
