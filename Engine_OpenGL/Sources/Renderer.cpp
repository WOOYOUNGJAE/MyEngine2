#include "pch.h"
#include "Renderer.h"
#include "MeshObject.h"

IMPL_COM_FUNC(CRenderer)

void CRenderer::BeginRender()
{
}

void CRenderer::Render_MeshObject(IMeshObject* pMeshObj)
{
	CMeshObject* pCastedMeshObj = reinterpret_cast<CMeshObject*>(pMeshObj);


	//pCastedMeshObj->VAO()
}

void CRenderer::EndRender()
{
}
