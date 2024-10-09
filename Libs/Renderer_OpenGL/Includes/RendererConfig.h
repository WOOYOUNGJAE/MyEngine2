#pragma once


#ifdef RendererOPENGL_EXPORTS
#define RendererOPENGL_DLL _declspec(dllexport)
#else
#define RendererOPENGL_DLL _declspec(dllimport)
#endif