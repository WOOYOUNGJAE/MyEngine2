#ifndef CUDACORECONFIG_H
#define CUDACORECONFIG_H


#ifdef CUDACORE_EXPORTS
#define CUDACORE_DLL _declspec(dllexport)
#else
#define CUDACORE_DLL _declspec(dllimport)
#endif



#endif