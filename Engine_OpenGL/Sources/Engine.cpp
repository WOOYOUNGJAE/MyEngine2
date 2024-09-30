#include "pch.h"
#include "Engine.h"
#include "Viewer.h"

CEngine::CEngine(IEngine::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle)
{
    // Init GL
    if (!glfwInit())
    {
        ERROR_MESSAGE("Init GLFW Failed");
        return;
    }

	// Create a GLFW window with OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Request OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // Double Buffering

    // Create Window, Context
    GLFWwindow* window = glfwCreateWindow((int)uiWinX, (int)uiWinY, szTitle, nullptr, nullptr);
    glfwMakeContextCurrent(window); // Bind Context

    // Init GLAD
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
    {
        ERROR_MESSAGE("Init GLAD Failed");
        return;
    }

    // Create Viewer
    m_pViewer = new CViewer(uiWinX, uiWinY);
}

CEngine::~CEngine()
{
    DELETE_INSTANCE(m_pViewer);
}

void CEngine::Engine_Tick(FLOAT fDeltaTime)
{
    if (m_pViewer == nullptr)
    {
        ERROR_MESSAGE("Viewer is Null");
        __debugbreak();
        return;
    }

    m_pViewer->BeginRender();
    m_pViewer->MainRender();
    m_pViewer->EndRender();
}
