#pragma once
#include "Renderer_Common/Includes/RendererInterface.h"

class CRenderMachine : public IRenderMachine
{
	COM_FUNC;
public:
	CRenderMachine() = default;
	~CRenderMachine() = default;
public:
	void BeginRender() override;
	void Render_MeshObject(IMeshObject* pMeshObj) override;
	void EndRender() override;
};

