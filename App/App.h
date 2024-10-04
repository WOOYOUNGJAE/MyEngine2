#pragma once
#include "resource.h"

interface IEngine;

INT Run_DirectX12(MSG& msg);
INT Run_OpenGL(IEngine* pEngine);
