// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef ENGINECOMMON_PCH_H
#define ENGINECOMMON_PCH_H

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

// Engine Common
#include "Macros.h"

// DirectX for Common
#include <SimpleMath.h>
#include <VertexTypes.h>
using namespace DirectX;
using namespace DirectX::SimpleMath;

#endif //ENGINECOMMON_PCH_H
