#include "pch.h"
#include "Game.h"

#include "Renderer_OpenGL/Includes/Renderer.h"
#include "Renderer_Common/Includes/PrimitiveGeomtryGenerator.h"
#include "Renderer_Common/Includes/Structs.h"
#include "TestGameObj.h"

IMPL_COM_FUNC(CGame)
CTestGameObj* pTestObj;
CGame::~CGame()
{
	for (auto& iterGameObj : m_GameObjList)
	{
		RELEASE_INSTANCE(iterGameObj);
	}
	RELEASE_INSTANCE(m_pRenderer);
}

HRESULT CGame::Initialize(std::string& strTitle)
{
	HRESULT hr = S_OK;

	// Select Graphics Api
	enum Graphics { DirectX12, OpenGL, Vulkan, Num };
	INT iGraphics = INT32_MAX;
	INT iRunResult = INT32_MAX;
	std::cout << "Select API\n1.DirectX12, 2.OpenGL\n: ";
	//std::cin >> iGraphics;
	//iGraphics -= 1;
	system("cls");
	iGraphics = OpenGL;

	UINT uiWinX = 1280, uiWinY = 720;


	if (iGraphics == OpenGL)
	{
		strTitle += " - OpenGL";
		m_pRenderer = new CRenderer(IRenderer::OpenGL(), uiWinX, uiWinY, strTitle.c_str());
	}
	else if (iGraphics >= Graphics::Num)
	{
		return FALSE;
	}


	// Init Scene (Temp)
	pTestObj = new CTestGameObj();
	pTestObj->Initialize(this);
	m_GameObjList.push_back(pTestObj);

#pragma region MyRegion0
	IMeshObject* pCubeMeshObj = m_pRenderer->Create_EmptyBasicMesh(); // Empty

	using namespace Renderer_Common;
	CREATE_MESHES_DESC createMeshDescInstance{};
	MESH_DESC_BASIC* basicMeshDescArr = new MESH_DESC_BASIC[1];
	::Fill_BasicMesh_Cube(basicMeshDescArr[0]);

	createMeshDescInstance.pBasicMeshDataArrPtr = &basicMeshDescArr;
	createMeshDescInstance.uiNumBasicMeshData = 1;

	pCubeMeshObj->Begin_CreateMesh(&createMeshDescInstance);
	pCubeMeshObj->End_CreateMesh();


	DELETE_ARRAY(basicMeshDescArr)
		DELETE_INSTANCE(pCubeMeshObj); // TODO TEMP  
#pragma endregion



	return hr;
}

void CGame::Run()
{
	BOOL bShouldClose = FALSE; // Result of Prev RendererTick

	while (true)
	{
		// Some Acting Change ShouldClose

		m_pRenderer->BeginRender();

		// Tick, Render, ...


		bShouldClose =
			m_pRenderer->Renderer_Tick(0.2f);
		if (bShouldClose)
			break;

		m_pRenderer->EndRender();
	}
}
