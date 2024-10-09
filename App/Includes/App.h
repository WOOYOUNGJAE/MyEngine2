#pragma once
#include "..\resource.h"

interface IRenderer;

INT Run_DirectX12(MSG& msg);
INT Run_OpenGL(IRenderer* pRenderer);

HRESULT Load_DLLs(HWND hwnd);