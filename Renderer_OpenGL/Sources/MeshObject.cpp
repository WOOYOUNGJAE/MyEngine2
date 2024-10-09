#include "pch.h"
#include "MeshObject.h"
#include "ShaderObject.h"
#include "RenderMachine.h"

IMPL_COM_FUNC(CMeshObject)

CMeshObject::~CMeshObject()
{
	DELETE_GL_BUFFER_OBJECT(m_EBO);
	DELETE_GL_VERTEX_ARRAY(m_VAO);
	DELETE_GL_BUFFER_OBJECT(m_VBO);
}

void CMeshObject::Begin_CreateMesh(void* pData)
{
	// 삼각형 개수, 버텍스 타입, 인덱스 어레이, 
	struct MESH_CREATE_DESC
	{
		

	};
}

void CMeshObject::End_CreateMesh(void* pData)
{
	glBindVertexArray(0); // Unbind VAO
}
