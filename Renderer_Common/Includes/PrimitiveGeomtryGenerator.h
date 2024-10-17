#pragma once
#include "Structs.h"

// DX Standard. Should be converted if OpenGL

inline void Fill_BasicMesh_Cube(Renderer_Common::MESH_DESC_BASIC& refMeshDesc)
{
	using namespace Renderer_Common;

	UINT uiNumVertices = 24;
	refMeshDesc.uiNumVertices = uiNumVertices;

	// Allocate
	refMeshDesc.fPositionArr = new FLOAT[3 * uiNumVertices]
	{
		// front
		-1.0f, -1.0f, -1.0f,
		-1.0f, +1.0f, -1.0f,
		+1.0f, +1.0f, -1.0f,
		+1.0f, -1.0f, -1.0f,
		// back
		-1.0f, -1.0f, +1.0f,
		-1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, -1.0f, +1.0f,
		// top
		-1.0f, +1.0f, -1.0f,
		-1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, -1.0f,
		// bottom
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, +1.0f,
		+1.0f, -1.0f, +1.0f,
		+1.0f, -1.0f, -1.0f,
		// left
		-1.0f, -1.0f, +1.0f,
		-1.0f, +1.0f, +1.0f,
		-1.0f, +1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		// right
		+1.0f, -1.0f, -1.0f,
		+1.0f, +1.0f, -1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, -1.0f, +1.0f
	};

	refMeshDesc.fNormalArr = new FLOAT[3 * uiNumVertices]
	{
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	refMeshDesc.fColorArr = new FLOAT[4 * uiNumVertices]
	{
		Colors::Yellow.f[0], Colors::Yellow.f[1], Colors::Yellow.f[2], Colors::Yellow.f[3],
		Colors::White.f[0], Colors::White.f[1], Colors::White.f[2], Colors::White.f[3],
		Colors::Cyan.f[0], Colors::Cyan.f[1], Colors::Cyan.f[2], Colors::Cyan.f[3],
		Colors::Green.f[0], Colors::Green.f[1], Colors::Green.f[2], Colors::Green.f[3],

		Colors::Red.f[0], Colors::Red.f[1], Colors::Red.f[2], Colors::Red.f[3],
		Colors::Magenta.f[0], Colors::Magenta.f[1], Colors::Magenta.f[2], Colors::Magenta.f[3],
		Colors::Blue.f[0], Colors::Blue.f[1], Colors::Blue.f[2], Colors::Blue.f[3],
		Colors::Black.f[0], Colors::Black.f[1], Colors::Black.f[2], Colors::Black.f[3],

		Colors::White.f[0], Colors::White.f[1], Colors::White.f[2], Colors::White.f[3],
		Colors::Magenta.f[0], Colors::Magenta.f[1], Colors::Magenta.f[2], Colors::Magenta.f[3],
		Colors::Blue.f[0], Colors::Blue.f[1], Colors::Blue.f[2], Colors::Blue.f[3],
		Colors::Cyan.f[0], Colors::Cyan.f[1], Colors::Cyan.f[2], Colors::Cyan.f[3],

		Colors::Yellow.f[0], Colors::Yellow.f[1], Colors::Yellow.f[2], Colors::Yellow.f[3],
		Colors::Red.f[0], Colors::Red.f[1], Colors::Red.f[2], Colors::Red.f[3],
		Colors::Black.f[0], Colors::Black.f[1], Colors::Black.f[2], Colors::Black.f[3],
		Colors::Green.f[0], Colors::Green.f[1], Colors::Green.f[2], Colors::Green.f[3],

		Colors::Red.f[0], Colors::Red.f[1], Colors::Red.f[2], Colors::Red.f[3],
		Colors::Magenta.f[0], Colors::Magenta.f[1], Colors::Magenta.f[2], Colors::Magenta.f[3],
		Colors::White.f[0], Colors::White.f[1], Colors::White.f[2], Colors::White.f[3],
		Colors::Yellow.f[0], Colors::Yellow.f[1], Colors::Yellow.f[2], Colors::Yellow.f[3],

		Colors::Green.f[0], Colors::Green.f[1], Colors::Green.f[2], Colors::Green.f[3],
		Colors::Cyan.f[0], Colors::Cyan.f[1], Colors::Cyan.f[2], Colors::Cyan.f[3],
		Colors::Blue.f[0], Colors::Blue.f[1], Colors::Blue.f[2], Colors::Blue.f[3],
		Colors::Black.f[0], Colors::Black.f[1], Colors::Black.f[2], Colors::Black.f[3],
	};

	refMeshDesc.fTexCoordArr = new FLOAT[2 * uiNumVertices]
	{
		0.0f, 1.0f,  // front
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,  // back
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,  // top
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,  // bottom
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,  // left
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 1.0f,  // right
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};


	UINT uiNumIndices = 36;
	refMeshDesc.uiNumIndices = uiNumIndices;
	refMeshDesc.indexArr = new UINT32[uiNumIndices]
	{
		// front
		0, 1, 2,
		0, 2, 3,

		// back
		7, 6, 5,
		7, 5, 4,

		// top
		8, 9, 10,
		8, 10, 11,

		// bottom
		13, 12, 15,
		13, 15, 14,

		// left
		16, 17, 18,
		16, 18, 19,

		// right
		20, 21, 22,
		20, 22, 23,
	};
}

inline void Fill_BasicMesh_Quad(Renderer_Common::MESH_DESC_BASIC& refMeshDesc)
{
	// TODO: GL Convention
	using namespace Renderer_Common;

	UINT uiNumVertices = 4;
	refMeshDesc.uiNumVertices = uiNumVertices;

	// Allocate
	refMeshDesc.fPositionArr = new FLOAT[3 * uiNumVertices]
	{
		0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	refMeshDesc.fNormalArr = new FLOAT[3 * uiNumVertices]
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	refMeshDesc.fColorArr = new FLOAT[4 * uiNumVertices]
	{
		Colors::Yellow.f[0], Colors::Yellow.f[1], Colors::Yellow.f[2], Colors::Yellow.f[3],
		Colors::White.f[0], Colors::White.f[1], Colors::White.f[2], Colors::White.f[3],
		Colors::Cyan.f[0], Colors::Cyan.f[1], Colors::Cyan.f[2], Colors::Cyan.f[3],
		Colors::Green.f[0], Colors::Green.f[1], Colors::Green.f[2], Colors::Green.f[3],
	};

	refMeshDesc.fTexCoordArr = new FLOAT[2 * uiNumVertices]
	{
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,
	};


	UINT uiNumIndices = 6;
	refMeshDesc.uiNumIndices = uiNumIndices;
	refMeshDesc.indexArr = new UINT32[uiNumIndices]
	{
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
}

#pragma region Static Mesh Info
struct STATIC_CUBE_BASIC_VERTEX
{
	UINT32 uiNumVertices = 24;
	UINT32 uiNumIndices = 36;
	DirectX::VertexPositionNormalColorTexture basicVertexArr[24]
	{
		// front
		VertexPositionNormalColorTexture(Vector3(-1, -1, -1), Vector3(0.0f, 0.0f, -1.0f), Colors::Yellow, Vector2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, +1, -1), Vector3(0.0f, 0.0f, -1.0f), Colors::White, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, +1, -1), Vector3(0.0f, 0.0f, -1.0f), Colors::Cyan, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, -1, -1), Vector3(0.0f, 0.0f, -1.0f), Colors::Green, Vector2(1.0f, 1.0f)),

		// back
		VertexPositionNormalColorTexture(Vector3(-1, -1, +1), Vector3(0.0f, 0.0f, 1.0f),Colors::Red,Vector2(1.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, +1, +1), Vector3(0.0f, 0.0f, 1.0f),Colors::Magenta, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, +1, +1), Vector3(0.0f, 0.0f, 1.0f),Colors::Blue, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, -1, +1), Vector3(0.0f, 0.0f, 1.0f),Colors::Black, Vector2(0.0f, 1.0f)),

		// top
		VertexPositionNormalColorTexture(Vector3(-1, +1, -1), Vector3(0.0f, 1.0f, 0.0f),Colors::White,Vector2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, +1, +1), Vector3(0.0f, 1.0f, 0.0f),Colors::Magenta, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, +1, +1), Vector3(0.0f, 1.0f, 0.0f),Colors::Blue, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, +1, -1), Vector3(0.0f, 1.0f, 0.0f),Colors::Cyan, Vector2(1.0f, 1.0f)),

		// bottom
		VertexPositionNormalColorTexture(Vector3(-1, -1, -1), Vector3(0.0f, -1.0f, 0.0f),Colors::Yellow,Vector2(1.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, -1, +1), Vector3(0.0f, -1.0f, 0.0f),Colors::Red, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, -1, +1), Vector3(0.0f, -1.0f, 0.0f),Colors::Black, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(+1, -1, -1), Vector3(0.0f, -1.0f, 0.0f),Colors::Green, Vector2(0.0f, 1.0f)),

		// left
		VertexPositionNormalColorTexture(Vector3(-1, -1, +1), Vector3(-1.0f, 0.0f, 0.0f),Colors::Red,Vector2(0.0f, 1.0f)),  // 
		VertexPositionNormalColorTexture(Vector3(-1, +1, +1), Vector3(-1.0f, 0.0f, 0.0f),Colors::Magenta, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, +1, -1), Vector3(-1.0f, 0.0f, 0.0f),Colors::White, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(-1, -1, -1), Vector3(-1.0f, 0.0f, 0.0f),Colors::Yellow, Vector2(1.0f, 1.0f)),

		// right
		VertexPositionNormalColorTexture(Vector3(1, -1, -1), Vector3(1.0f, 0.0f, 0.0f), Colors::Green,Vector2(0.0f, 1.0f)),
		VertexPositionNormalColorTexture(Vector3(1, +1, -1), Vector3(1.0f, 0.0f, 0.0f), Colors::Cyan, Vector2(0.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(1, +1, +1), Vector3(1.0f, 0.0f, 0.0f), Colors::Blue, Vector2(1.0f, 0.0f)),
		VertexPositionNormalColorTexture(Vector3(1, -1, +1), Vector3(1.0f, 0.0f, 0.0f), Colors::Black, Vector2(1.0f, 1.0f)),

	};
	UINT32 indexArr[36]
	{
		// front
		0, 1, 2,
		0, 2, 3,

		// back
		7, 6, 5,
		7, 5, 4,

		// top
		8, 9, 10,
		8, 10, 11,

		// bottom
		13, 12, 15,
		13, 15, 14,

		// left
		16, 17, 18,
		16, 18, 19,

		// right
		20, 21, 22,
		20, 22, 23,
	};
};
#pragma endregion
