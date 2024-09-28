#include "pch.h"
#include "Renderer.h"

CRenderer::CRenderer(IRenderer::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle)
{
    if (!glfwInit())
    {
        ERROR_MESSAGE("Init GLFW Failed");
        return;
    }

	// Create a GLFW window with OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Request OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window, Context
    GLFWwindow* window = glfwCreateWindow((int)uiWinX, (int)uiWinY, szTitle, nullptr, nullptr);
    glfwMakeContextCurrent(window); // Bind Context

    // Init GLAD
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
    {
        ERROR_MESSAGE("Init GLAD Failed");
        return;
    }


}

//#include "Test.h"
CRenderer::~CRenderer()
{
}
