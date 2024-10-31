#include "pch.h"
#include "CUDA_Core.h"
#include "CudaResource.h"
#include "CudaResource_GS.h"

#include "Engine_Core/Includes/Asset_ply.h"

IMPL_COM_FUNC(CCUDA_Core)

CCUDA_Core::CCUDA_Core()
{
	CUDA_SAFE_CALL_ALWAYS(cudaGetDeviceCount(&m_iDeviceNum));

	if (m_iDeviceNum <= 0)
	{
		__debugbreak();
		return;
	}


}

CCUDA_Core::~CCUDA_Core()
{
	for (auto& iterResource : m_pCudaResourceArr)
	{
		RELEASE_INSTANCE(iterResource);
	}
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


	m_pCudaResourceArr[Cuda_Core::GS] = pResourceInstance;
	for (UINT i = 0; i < iNum; ++i)
	{
		pResourceInstance->Create_GaussianCudaData(pLoadedPlyArr[i]);		
	}
}
