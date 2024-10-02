#pragma once

typedef std::vector<glm::vec3> POSITIONS;
typedef std::vector<glm::vec3> NORMALS;
typedef std::vector<glm::vec4> COLORS;

namespace GL
{
	using namespace glm;
	struct VertexPositionNormalColor
	{
		vec3 position;
		vec3 normal;
		vec4 color;
	};
}