#include "pch.h"
#include "CudaResource.h"

IMPL_COM_FUNC(CCudaResource)

CCudaResource::CCudaResource(int iDeviceIndex) : m_iDeviceIndex(iDeviceIndex)
{
	cudaDeviceProp prop;
	CUDA_SAFE_CALL_ALWAYS(cudaGetDeviceProperties(&prop, iDeviceIndex));
	if (prop.major < 7)
	{
		std::cerr << "Sorry, need at least compute capability 7.0+!";
	}
}

CCudaResource::~CCudaResource()
{
}
