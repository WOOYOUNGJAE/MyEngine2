#include "pch.h"
#include "Renderer.h"

CRenderer::CRenderer(IRenderer::OpenGL identifier)
{
    if (!glfwInit())
    {
        return;
    }

	// Create a GLFW window with OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Request OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Version Check", nullptr, nullptr);
   
}

//#include "Test.h"
CRenderer::~CRenderer()
{
}
