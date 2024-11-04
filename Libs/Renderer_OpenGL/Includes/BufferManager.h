#pragma once
/**
 * @brief Manage GL Buffers that should be Managed by Core
 */
class CBufferManager : public IUnknown
{
	COM_BASE
public:
	CBufferManager() = default;
	~CBufferManager();
public:
	void Generate_Buffer_CudaImage(UINT winX, UINT winY);
	GLuint* Get_ImageBuffer() { return &m_imageBuffer; } // Get ImageBuffer (for Cuda, ...)
private:
	GLuint m_imageBuffer = 0; // for Cuda (probably to be chagned)

};

