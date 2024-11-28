#pragma once

#include "Config.h"
namespace Cuda_Core
{
	enum CUDA_RESOURCE_TYPE {GS, CUDA_RESOURCE_TYPE_NUM};
}

class CCudaResource;
class CAsset_ply;
interface IRenderer;
class CUDA_DLL CCUDA_Core : public IUnknown
{
	COM_BASE
public:
	CCUDA_Core() = delete;
	CCUDA_Core(IRenderer* pRenderer, UINT uiWinX, UINT uiWinY);
	virtual ~CCUDA_Core();

public:
	void Create_CudaResource_GS(CAsset_ply* pLoadedPly);
	void Create_CudaResource_GS(CAsset_ply** pLoadedPlyArr, UINT iNum);

private:
	CCudaResource* m_pCudaResourceArr[Cuda_Core::CUDA_RESOURCE_TYPE_NUM]{};
	INT m_iDeviceNum = 0;
private: // pointer
	IRenderer* m_pRenderer = nullptr;
};

