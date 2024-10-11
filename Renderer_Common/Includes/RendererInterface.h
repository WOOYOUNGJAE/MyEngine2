#pragma once
#include "RendererConfig.h"

interface RENDERERCOMMON_DLL IVertex {};


interface RENDERERCOMMON_DLL IMeshObject : public IUnknown
{
	IMeshObject() = default;
	virtual ~IMeshObject() = default;

	virtual void Begin_CreateMesh(void* pData = nullptr) = 0;
	virtual void End_CreateMesh(void* pData = nullptr) = 0;
};

//interface RENDERERCOMMON_DLL IRenderMachine : public IUnknown
//{
//	IRenderMachine() = default;
//	virtual ~IRenderMachine() = default;
//
//	// Render Func
//	virtual void BeginRender() = 0;
//	virtual void EndRender() = 0;
//};

interface RENDERERCOMMON_DLL IRenderer : public IUnknown
{
	IRenderer() = default;
	virtual ~IRenderer() = default;
	class OpenGL {};
	class DirectX12 {};

	// getter
	//virtual IRenderMachine* Get_RenderMachine() = 0;

	virtual void Initialize(void* = nullptr) = 0;
	virtual INT MainRender(FLOAT fDeltaTime = 0.2f) = 0;
	// Render Func
	virtual void BeginRender() = 0;
	virtual void Render_MeshObject(IMeshObject* pMeshObj) = 0;
	virtual void EndRender() = 0;

	// Create Only Empty Mesh, Mesh Calls Actual Init Itself.
	virtual IMeshObject* Create_EmptyColoredMesh(void* pData = nullptr) = 0; // TODO: delete
	virtual IMeshObject* Create_EmptyBasicMesh(void* pData = nullptr) = 0;
};