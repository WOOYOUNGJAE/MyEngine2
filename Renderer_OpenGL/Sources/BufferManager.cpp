#include "pch.h"
#include "BufferManager.h"

IMPL_COM_FUNC(CBufferManager)

CBufferManager::~CBufferManager()
{
	DELETE_GL_BUFFER_OBJECT(m_imageBuffer);
}

void CBufferManager::Generate_Buffer_CudaImage(UINT winX, UINT winY)
{
	glCreateBuffers(1, &m_imageBuffer);
	glNamedBufferStorage(m_imageBuffer, GLsizeiptr(winX * winY * 3 * sizeof(float)), nullptr, GL_DYNAMIC_STORAGE_BIT);
}
