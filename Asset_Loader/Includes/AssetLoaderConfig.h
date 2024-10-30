#pragma once

#ifdef ASSETLOADER_EXPORTS
#define ASSETLOADER_DLL _declspec(dllexport)
#else
#define ASSETLOADER_DLL _declspec(dllimport)
#endif