#pragma once

class CCudaResource : public IUnknown
{
	COM_BASE
public:
	CCudaResource(int iDeviceIndex);
	CCudaResource() = delete;
	virtual ~CCudaResource();

private:
	int m_iDeviceIndex = -1;
};