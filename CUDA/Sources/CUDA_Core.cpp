#include "pch.h"
#include "CUDA_Core.h"
#include "CudaResource.h"
#include "CudaResource_GS.h"
#include "Optix_Engine.h"
#include "Engine_Core/Includes/Asset_ply.h"

#include "Common/Includes/RendererInterface.h"
#include "Renderer_OpenGL/Includes/Renderer.h"


IMPL_COM_FUNC(CCUDA_Core)

CCUDA_Core::CCUDA_Core(IRenderer* pRenderer, UINT uiWinX, UINT uiWinY) : m_pRenderer(pRenderer)
{
	ADDREF_INSTANCE(m_pRenderer)
	CUDA_SAFE_CALL_ALWAYS(cudaGetDeviceCount(&m_iDeviceNum));

	if (m_iDeviceNum <= 0)
	{
		__debugbreak();
		return;
	}

	// TODO Temp
	COptix_Engine* pOptix = new COptix_Engine(uiWinX, uiWinY);
}

CCUDA_Core::~CCUDA_Core()
{
	for (auto& iterResource : m_pCudaResourceArr)
	{
		RELEASE_INSTANCE(iterResource);
	}

	RELEASE_INSTANCE(m_pRenderer);
}

void CCUDA_Core::Create_CudaResource_GS(CAsset_ply* pLoadedPly)
{
	int iCurDeviceIndex = m_iDeviceNum - 1;

	CCudaResource_GS* pResourceInstance = new CCudaResource_GS(iCurDeviceIndex);
	CUDA_SAFE_CALL_ALWAYS(cudaSetDevice(iCurDeviceIndex));

	pResourceInstance->Create_GaussianCudaData(pLoadedPly);

	m_pCudaResourceArr[Cuda_Core::GS] = pResourceInstance;
}

void CCUDA_Core::Create_CudaResource_GS(CAsset_ply** pLoadedPlyArr, UINT iNum)
{
	int iCurDeviceIndex = m_iDeviceNum - 1;
	CCudaResource_GS* pResourceInstance = new CCudaResource_GS(iCurDeviceIndex);
	CUDA_SAFE_CALL_ALWAYS(cudaSetDevice(iCurDeviceIndex));


	for (UINT i = 0; i < iNum; ++i)
	{
		pResourceInstance->Create_GaussianCudaData(pLoadedPlyArr[i]);		
	}

	if (m_pRenderer->m_eGraphics == Graphics_API::OpenGL)
	{
		pResourceInstance->Register_GraphicResource_OpenGL(*(GLuint*)m_pRenderer->Get_ImageBuffer());
	}

	m_pCudaResourceArr[Cuda_Core::GS] = pResourceInstance;
}
