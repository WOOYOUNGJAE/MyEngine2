#pragma once

#ifdef COMMON_EXPORTS
#define COMMON_DLL _declspec(dllexport)
#else
#define COMMON_DLL _declspec(dllimport)
#endif