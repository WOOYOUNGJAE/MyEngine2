#pragma once

#include "Config.h"

namespace Cuda_Core
{
	enum CUDA_RESOURCE_TYPE {GS, CUDA_RESOURCE_TYPE_NUM};
}

class CCudaResource;
class CAsset_ply;
class CUDACORE_DLL CCUDA_Core : public IUnknown
{
	COM_BASE
public:
	CCUDA_Core();
	virtual ~CCUDA_Core();

public:
	void Create_CudaResource_GS(CAsset_ply* pLoadedPly);
	void Create_CudaResource_GS(CAsset_ply** pLoadedPlyArr, UINT iNum);

private:
	CCudaResource* m_pCudaResourceArr[Cuda_Core::CUDA_RESOURCE_TYPE_NUM]{};
	INT m_iDeviceNum = 0;
};

