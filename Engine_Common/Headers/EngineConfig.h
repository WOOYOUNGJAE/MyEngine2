#pragma once

#ifdef ENGINECOMMON_EXPORTS
#define ENGINECOMMON_DLL _declspec(dllexport)
#else
#define ENGINECOMMON_DLL _declspec(dllimport)
#endif