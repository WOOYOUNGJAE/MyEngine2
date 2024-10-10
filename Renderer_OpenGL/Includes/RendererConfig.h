#pragma once


#ifdef RENDEREROPENGL_EXPORTS
#define RENDEREROPENGL_DLL _declspec(dllexport)
#else
#define RENDEREROPENGL_DLL _declspec(dllimport)
#endif