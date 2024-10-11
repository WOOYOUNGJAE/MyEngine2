#version 330 core

in vec4 fragColor;                             // Input color from vertex shader
in vec2 fragTexCoord;                          // Input texture coordinate from vertex shader

out vec4 finalColor;                           // Final color output

void main()
{
    finalColor = fragColor;                    // Output the color received from the vertex shader
}
