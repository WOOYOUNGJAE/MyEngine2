#pragma once

#ifdef RendererCOMMON_EXPORTS
#define RendererCOMMON_DLL _declspec(dllexport)
#else
#define RendererCOMMON_DLL _declspec(dllimport)
#endif