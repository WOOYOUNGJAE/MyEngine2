// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"

// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.

#if defined(_M_AMD64)
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\bin\\D3D12\\x64\\"; }
#elif defined(_M_IX86)
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\bin\\D3D12\\x86\\"; }
#endif