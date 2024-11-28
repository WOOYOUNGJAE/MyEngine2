#pragma once
#include "RendererConfig.h"
#include "Structs.h"


enum Graphics_API { DirectX12, OpenGL, Vulkan, Num };

interface COMMON_DLL IVertex {};


interface COMMON_DLL IMeshObject : public IUnknown
{
	IMeshObject() = default;
	virtual ~IMeshObject() = default;

	virtual void Begin_CreateMesh(void* pData = nullptr) = 0;
	virtual void End_CreateMesh(void* pData = nullptr) = 0;

	XMFLOAT4X4 WorldMat() { return m_matWorld; }
	void Set_WorldMat(const XMFLOAT4X4& matWorld) { m_matWorld = matWorld; }
protected:
	XMFLOAT4X4 m_matWorld; // DirectX Math

};

//interface COMMON_DLL IRenderMachine : public IUnknown
//{
//	IRenderMachine() = default;
//	virtual ~IRenderMachine() = default;
//
//	// Render Func
//	virtual void BeginRender() = 0;
//	virtual void EndRender() = 0;
//};

interface COMMON_DLL IRenderer : public IUnknown
{
	IRenderer() = default;
	virtual ~IRenderer() = default;
	class OpenGL {};
	class DirectX12 {};

	// getter
	//virtual IRenderMachine* Get_RenderMachine() = 0;

	virtual void Initialize(void* pArg= nullptr) = 0;
	virtual void Update_CameraInfo(XMFLOAT4X4& matCameraWorld, CAMERA_DESC& cameraDesc) = 0;
	virtual INT MainRender(FLOAT fDeltaTime = 0.2f) = 0;
	// Render Func
	virtual void BeginRender() = 0;
	/**
	 * Called from External Renderer
	 */
	virtual void Render_MeshObject_External(IMeshObject* pMeshObj, XMFLOAT4X4& matWorld) = 0;
	virtual void MainRender() = 0;
	virtual void EndRender() = 0;

	virtual IMeshObject* Create_EmptyBasicMesh(void* pData = nullptr) = 0;

	// Resource
	virtual void* Get_ImageBuffer() = 0;
public:
	Graphics_API m_eGraphics = Graphics_API::Num;
};
