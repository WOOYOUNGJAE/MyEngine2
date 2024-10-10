#pragma once

namespace Engine_Common
{


	// Vertex(Position, Normal, Color, Texcoord), Index(uint16)
	struct MESH_DESC_BASIC
	{
		MESH_DESC_BASIC() = default;
		~MESH_DESC_BASIC()
		{
			DELETE_ARRAY(fPositionArr);
			DELETE_ARRAY(fNormalArr);
			DELETE_ARRAY(fColorArr);
			DELETE_ARRAY(fTexCoordArr);
			DELETE_ARRAY(indexArr);
		}
		// Vertex
		UINT uiNumVertices = 0;
		FLOAT* fPositionArr = nullptr; // POSITION: xyz * numVertices
		FLOAT* fNormalArr = nullptr; // NORMAL: xyz * numVertices
		FLOAT* fColorArr = nullptr; // COLOR: rgba * numVertices
		FLOAT* fTexCoordArr = nullptr; // UV: uv * numVertices

		// Indices
		UINT uiNumIndices = 0;
		UINT16* indexArr = nullptr;
	};

	/**
	 * @brief Only Contain Pointer of Array. DO NOT DELETE ARRAY
	 */
	struct CREATE_MESHES_DESC
	{
		CREATE_MESHES_DESC() = default;
		CREATE_MESHES_DESC(MESH_DESC_BASIC** pInBasicMeshDataArrPtr, UINT uiInNumBasicMeshData) : pBasicMeshDataArrPtr(pInBasicMeshDataArrPtr), uiNumBasicMeshData(uiInNumBasicMeshData)
		{
		}
		~CREATE_MESHES_DESC() = default;
		MESH_DESC_BASIC** pBasicMeshDataArrPtr = nullptr;
		UINT uiNumBasicMeshData = 0;
	};
}