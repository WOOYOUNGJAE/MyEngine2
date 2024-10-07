#pragma once
#include "EngineConfig.h"

interface ENGINECOMMON_DLL IVertex {};


interface ENGINECOMMON_DLL IMeshObject : public IUnknown
{
	virtual void Begin_CreateMesh(void* pData = nullptr) = 0;
	virtual void End_CreateMesh(void* pData = nullptr) = 0;
};

interface ENGINECOMMON_DLL IEngine : public IUnknown
{
	class OpenGL {};
	class DirectX12 {};

	virtual HRESULT Initialize(void*) = 0;
	virtual INT Engine_Tick(FLOAT fDeltaTime = 0.2f) = 0;
	// Render Func
	virtual void BeginRender() = 0;
	virtual void MainRender() = 0;
	virtual void EndRender() = 0;

	// Create Mesh
	virtual IMeshObject* Create_EmptyColoredMesh(void* pData = nullptr) = 0;
};