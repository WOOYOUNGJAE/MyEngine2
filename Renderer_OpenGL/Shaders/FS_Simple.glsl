#version 330 core

in vec4 fragColor;                             // Input color from vertex shader
in vec2 fragTexCoord;                          // Input texture coordinate from vertex shader

out vec4 finalColor;                           // Final color output

void main()
{
    finalColor = fragColor;                    // Output the color received from the vertex shader
    //finalColor = vec4(0.0f, 0.5f, 0.2f, 1.0f);                // Output the color received from the vertex shader
}


//
//#version 330 core
//out vec4 FragColor;
//
//void main()
//{
//    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//}