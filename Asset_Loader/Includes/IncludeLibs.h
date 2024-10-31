#ifndef ASSETLOADERINCLUDELIBS_H
#define ASSETLOADERINCLUDELIBS_H

#include "Engine_Core/Includes/IncludeLibs.h"


#ifdef _WIN64 // x64
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Engine_Core/bin/Engine_Core_x64_Debug.lib")
#else
#pragma comment(lib, "../Libs/Engine_Core/bin/Engine_Core_x64_Release.lib")
#endif
#else // (x86)
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Engine_Core/bin/Engine_Core_x86_Debug.lib")
#else
#pragma comment(lib, "../Libs/Engine_Core/bin/Engine_Core_x86_Release.lib")
#endif
#endif


#endif