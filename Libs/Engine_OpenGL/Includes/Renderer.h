#pragma once
#include "Engine_Common/Includes/EngineInterface.h"

class CRenderer : public IRenderer
{
	COM_FUNC;
public:
	CRenderer() = default;
	~CRenderer() = default;
public:
	void BeginRender() override;
	void Render_MeshObject(IMeshObject* pMeshObj) override;
	void EndRender() override;
};

