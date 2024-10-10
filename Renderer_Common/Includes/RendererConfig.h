#pragma once

#ifdef RENDERERCOMMON_EXPORTS
#define RENDERERCOMMON_DLL _declspec(dllexport)
#else
#define RENDERERCOMMON_DLL _declspec(dllimport)
#endif