#include "pch.h"
#include "TestGameObj.h"

#include "RendererInterface.h"
#include "Game.h"
#include "PrimitiveGeomtryGenerator.h"
#include "Structs.h"

IMPL_COM_FUNC(CTestGameObj)

CTestGameObj::~CTestGameObj()
{
	RELEASE_INSTANCE(m_pMeshObj);
}

void CTestGameObj::Initialize(CGame* pGame)
{
	m_pRenderMachine = pGame->m_pRenderMachine;

	m_pMeshObj = pGame->m_pRenderer->Create_EmptyBasicMesh(); // Empty

	using namespace Renderer_Common;
	CREATE_MESHES_DESC createMeshDescInstance{};
	MESH_DESC_BASIC* basicMeshDescArr = new MESH_DESC_BASIC[1];
	::Fill_BasicMesh_Cube(basicMeshDescArr[0]);

	createMeshDescInstance.pBasicMeshDataArrPtr = &basicMeshDescArr;
	createMeshDescInstance.uiNumBasicMeshData = 1;

	m_pMeshObj->Begin_CreateMesh(&createMeshDescInstance);
	m_pMeshObj->End_CreateMesh();


	DELETE_ARRAY(basicMeshDescArr)
}

void CTestGameObj::Tick(FLOAT fDeltaTime)
{

}

void CTestGameObj::Late_Tick(FLOAT fDeltaTime)
{
}

void CTestGameObj::Render()
{
	m_pRenderMachine->Render_MeshObject(m_pMeshObj);
}
