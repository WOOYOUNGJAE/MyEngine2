#pragma once
#include "CudaResource.h"
#include "Structs.h"
class CAsset_ply;
class CCudaResource_GS : public CCudaResource
{
public:
	CCudaResource_GS(int iDeviceIndex);
	CCudaResource_GS() = delete;
	~CCudaResource_GS() override;
public:
	void Create_GaussianCudaData(CAsset_ply* pLoadedPly);

private:
	std::list<GS::GAUSSIANS_CUDA_DATA*> m_pGaussianCudaDataList;
	std::list<GS::UNIFORM_CUDA_DATA*> m_pUniformCudaDataList;
};

