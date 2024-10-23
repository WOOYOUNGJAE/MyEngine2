#version 330 core

layout(location = 0) in vec3 position;         // Vertex position
layout(location = 1) in vec3 normal;           // Vertex normal
layout(location = 2) in vec4 color;            // Vertex color
layout(location = 3) in vec2 texCoord;         // Texture coordinate

out vec4 fragColor;                             // Output color to the fragment shader
out vec2 fragTexCoord;                          // Output texture coordinate to the fragment shader

uniform mat4 g_Model;                             // Model matrix
uniform mat4 g_ViewProj;                              // View * Proj

void main()
{
    gl_Position = vec4(position, 1.0); // Transform vertex position
    gl_Position = g_Model * vec4(position, 1.0); // Transform vertex position
    gl_Position = g_ViewProj * g_Model * vec4(position, 1.0); // Transform vertex position
    fragColor = color;                          // Pass color to fragment shader
    fragTexCoord = texCoord;                   // Pass texture coordinate to fragment shader
}
