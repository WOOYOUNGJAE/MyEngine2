#pragma once

#ifdef ENGINECORE_EXPORTS
#define ENGINECORE_DLL _declspec(dllexport)
#else
#define ENGINECORE_DLL _declspec(dllimport)
#endif