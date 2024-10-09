#include "pch.h"
#include "Game.h"

#include "Engine_OpenGL/Includes/Engine.h"
#include "Engine_Common/Includes/PrimitiveGeomtryGenerator.h"
#include "Engine_Common/Includes/Structs.h"

IMPL_COM_FUNC(CGame)

CGame::~CGame()
{
	if (m_pEngine)
	{
		m_pEngine->Release();
	}
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
		m_pEngine = new CEngine(IEngine::OpenGL(), uiWinX, uiWinY, strTitle.c_str());
	}
	else if (iGraphics >= Graphics::Num)
	{
		return FALSE;
	}


	// Init Scene (Temp)
	IMeshObject* pCubeMeshObj = m_pEngine->Create_EmptyBasicMesh(); // Empty

	using namespace Engine_Common;
	CREATE_MESHES_DESC createMeshDescInstance{};
	MESH_DESC_BASIC* basicMeshDescArr = new MESH_DESC_BASIC[1];
	::Fill_BasicMesh_Cube(basicMeshDescArr[0]);
	
	createMeshDescInstance.pBasicMeshDataArrPtr = &basicMeshDescArr;
	createMeshDescInstance.uiNumBasicMeshData = 1;

	pCubeMeshObj->Begin_CreateMesh(&createMeshDescInstance); // TODO: pBasicMeshDescArr[0] is ??, 1 is 1

	//if (createMeshDescInstance.pBasicMeshDataArr)
	//{								
	//	delete[] createMeshDescInstance.pBasicMeshDataArr;
	//	createMeshDescInstance.pBasicMeshDataArr = nullptr;
	//}

	DELETE_ARRAY(basicMeshDescArr)
	DELETE_INSTANCE(pCubeMeshObj); // TODO TEMP

	return hr;
}

void CGame::Run()
{
	BOOL bShouldClose = FALSE; // Result of Prev EngineTick

	while (true)
	{
		// Some Acting Change ShouldClose

		// Tick, Render, ...
		bShouldClose =
			m_pEngine->Engine_Tick(0.2f);

		if (bShouldClose)
			break;
	}
}
