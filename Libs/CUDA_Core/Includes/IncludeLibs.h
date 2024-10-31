#ifndef CUDACOREINCLUDELIBS_H
#define CUDACOREINCLUDELIBS_H

#ifdef _WIN64 // x64
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Common/bin/Common_x64_Debug.lib")
#else
#pragma comment(lib, "../Libs/Common/bin/Common_x64_Release.lib")
#endif
#else // (x86)
#ifdef _DEBUG
#pragma comment(lib, "../Libs/Common/bin/Common_x86_Debug.lib")
#else
#pragma comment(lib, "../Libs/Common/bin/Common_x86_Release.lib")
#endif
#endif


#include "Common/Includes/pch.h"

#endif