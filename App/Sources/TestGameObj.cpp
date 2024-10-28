#include "pch.h"
#include "TestGameObj.h"

#include "Renderer_Common/Includes/RendererInterface.h"
#include "Renderer_Common/Includes/PrimitiveGeomtryGenerator.h"
#include "Renderer_Common/Includes/Structs.h"

#include "Engine_Core/Includes/Engine_Core.h"

#include "Game.h"

CTestGameObj::~CTestGameObj()
{
	RELEASE_INSTANCE(m_pMeshObj);
}

void CTestGameObj::Initialize(CEngine_Core* pEngine)
{
	m_pRenderer = pEngine->m_pRenderer;

	m_pMeshObj = pEngine->m_pRenderer->Create_EmptyBasicMesh(); // Empty

	using namespace Renderer_Common;
	CREATE_MESHES_DESC createMeshDescInstance{};
	MESH_DESC_BASIC* basicMeshDescArr = new MESH_DESC_BASIC[2];
	::Fill_BasicMesh_Cube(basicMeshDescArr[0]);
	::Fill_BasicMesh_Quad(basicMeshDescArr[1]);

	//createMeshDescInstance.pBasicMeshDataArrPtr = &basicMeshDescArr;
	createMeshDescInstance.pBasicMeshDataArrPtr = &basicMeshDescArr;
	createMeshDescInstance.uiNumBasicMeshData = 2;

	m_pMeshObj->Begin_CreateMesh(&createMeshDescInstance);
	m_pMeshObj->End_CreateMesh();


	DELETE_ARRAY(basicMeshDescArr);
}

void CTestGameObj::Tick(FLOAT fDeltaTime)
{
	static float fAccAngle = 0.f;
	fAccAngle = fDeltaTime * 0.07f;
	Quaternion rot;
	rot = Quaternion::CreateFromAxisAngle(Vector3::Up, fAccAngle);
	rot = Quaternion::CreateFromAxisAngle(Vector3::Right, fAccAngle);
	//m_pTransform.Multiple_Rotation(Matrix::CreateFromQuaternion(rot));;
}

void CTestGameObj::Late_Tick(FLOAT fDeltaTime)
{
	CGameObject::Late_Tick(fDeltaTime);
}

void CTestGameObj::Render()
{
	m_pRenderer->Render_MeshObject_External(m_pMeshObj, m_pTransform.WorldMatrix());
}
