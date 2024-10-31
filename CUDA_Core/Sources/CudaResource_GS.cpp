#include "pch.h"
#include "CudaResource_GS.h"

#include "Engine_Core/Includes/Asset_ply.h"

CCudaResource_GS::CCudaResource_GS(int iDeviceIndex) : CCudaResource(iDeviceIndex)
{
	
}

CCudaResource_GS::~CCudaResource_GS()
{
	for (auto& iterGaussianData : m_pGaussianCudaDataList)
	{
		DELETE_INSTANCE(iterGaussianData);
	}
	m_pGaussianCudaDataList.clear();
	for (auto& iterUniformData : m_pUniformCudaDataList)
	{
		DELETE_INSTANCE(iterUniformData);
	}
	m_pUniformCudaDataList.clear();

}

void CCudaResource_GS::Create_GaussianCudaData(CAsset_ply* pLoadedPly)
{
	UINT iNumPoints = pLoadedPly->m_iNumPoints;

	GS::GAUSSIANS_CUDA_DATA* pGaussianData = new GS::GAUSSIANS_CUDA_DATA();

	// Allocate the GPU data - GaussianData
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&(pGaussianData->posXYZArr), sizeof(XMFLOAT3) * iNumPoints));
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&(pGaussianData->rotXYZWArr), sizeof(XMFLOAT4) * iNumPoints));
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&(pGaussianData->scaleXYZArr), sizeof(XMFLOAT3) * iNumPoints));
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&(pGaussianData->opacityArr), sizeof(FLOAT) * iNumPoints));
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&(pGaussianData->shsArr), sizeof(SHs<iFixedDimension>) * iNumPoints));
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&(pGaussianData->normalXYZArr), sizeof(XMFLOAT3) * iNumPoints));

	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&pGaussianData->bg_colorXYZ, 3 * sizeof(float)));
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&pGaussianData->rect, 2 * iNumPoints * sizeof(int)));

	// Fill GaussianData
	CUDA_SAFE_CALL_ALWAYS(cudaMemcpy(pGaussianData->posXYZArr, pLoadedPly->m_vecPos.data(), sizeof(XMFLOAT3) * iNumPoints, cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL_ALWAYS(cudaMemcpy(pGaussianData->rotXYZWArr, pLoadedPly->m_vecRot.data(), sizeof(XMFLOAT4) * iNumPoints, cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL_ALWAYS(cudaMemcpy(pGaussianData->scaleXYZArr, pLoadedPly->m_vecScale.data(), sizeof(XMFLOAT3) * iNumPoints, cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL_ALWAYS(cudaMemcpy(pGaussianData->opacityArr, pLoadedPly->m_vecOpacity.data(), sizeof(FLOAT) * iNumPoints, cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL_ALWAYS(cudaMemcpy(pGaussianData->shsArr, pLoadedPly->m_vecShs.data(), sizeof(SHs<iFixedDimension>) * iNumPoints, cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL_ALWAYS(cudaMemcpy(pGaussianData->normalXYZArr, pLoadedPly->m_vecNormal.data(), sizeof(XMFLOAT3) * iNumPoints, cudaMemcpyHostToDevice));

	float bgXYZ[3] = {0.4f, 0.4f, 0.4f};
	CUDA_SAFE_CALL_ALWAYS(cudaMemcpy(pGaussianData->bg_colorXYZ, bgXYZ, 3 * sizeof(float), cudaMemcpyHostToDevice));

	m_pGaussianCudaDataList.push_back(pGaussianData);

	GS::UNIFORM_CUDA_DATA* pUniformCudaData = new GS::UNIFORM_CUDA_DATA();
	// Create space for view parameters
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&pUniformCudaData->viewMat4X4, sizeof(XMFLOAT4X4)));
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&pUniformCudaData->projMat4X4, sizeof(XMFLOAT4X4)));
	CUDA_SAFE_CALL_ALWAYS(cudaMalloc((void**)&pUniformCudaData->camPosXYZ, 3 * sizeof(FLOAT)));

	m_pUniformCudaDataList.push_back(pUniformCudaData);
}
