#pragma once

using namespace glm;

typedef std::vector<glm::vec3> POSITIONS;
typedef std::vector<glm::vec3> NORMALS;
typedef std::vector<glm::vec4> COLORS;
typedef std::vector<glm::vec2> TEXCOORDS;

namespace GL
{
	interface VertexType{};
	using namespace glm;
	struct VertexPositionNormalColor : public VertexType
	{
		vec3 position;
		vec3 normal;
		vec4 color;
	};
	struct VertexPositionNormalColorTexture : public VertexType
	{
		vec3 position;
		vec3 normal;
		vec4 color;
		vec2 textureCoordinate;
	};
}