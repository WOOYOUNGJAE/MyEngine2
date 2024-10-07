#pragma once


#ifdef ENGINEOPENGL_EXPORTS
#define ENGINEOPENGL_DLL _declspec(dllexport)
#else
#define ENGINEOPENGL_DLL _declspec(dllimport)
#endif