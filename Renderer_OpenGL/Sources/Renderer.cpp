#include "pch.h"
#include "Renderer.h"

#include "BasicMesh.h"
#include "Viewer.h"

IMPL_COM_FUNC(CRenderer)

CViewer* g_pViewer;
void On_Resize_Window(GLFWwindow* pWindow, INT winX, INT winY);

void On_Resize_Window(GLFWwindow* pWindow, INT winX, INT winY)
{
    glViewport(0, 0, winX, winY);
    if (g_pViewer)
    {
		g_pViewer->On_Resize_Window((UINT)winX, (UINT)winY);	    
    }
}

CRenderer::CRenderer(IRenderer::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle)
{
    // Init GL
    if (!glfwInit())
    {
        ERROR_BOX("Init GLFW Failed");
        return;
    }

	// Create a GLFW window with OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Request OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // Double Buffering

    // Create Window, Context
    m_pWindow = glfwCreateWindow((int)uiWinX, (int)uiWinY, szTitle, nullptr, nullptr);
    glfwMakeContextCurrent(m_pWindow); // Bind Context

    // Init GLAD
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
    {
        ERROR_BOX("Init GLAD Failed");
        return;
    }

    // Create Viewer
    m_pViewer = new CViewer(uiWinX, uiWinY, this);
    g_pViewer = m_pViewer;

    // Register Callback win Resizing Func
    glfwSetFramebufferSizeCallback(m_pWindow, On_Resize_Window);
}

CRenderer::~CRenderer()
{
    DELETE_INSTANCE(m_pViewer);
}

HRESULT CRenderer::Initialize(void*)
{
    HRESULT hr = S_OK;


    return hr;
}

int32 CRenderer::Renderer_Tick(FLOAT fDeltaTime)
{

    if (m_pViewer == nullptr)
    {
        ERROR_BOX("Viewer is Null");
        __debugbreak();
        return TRUE;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_pWindow, true);
        glfwTerminate();
        return TRUE;
    }


    glfwPollEvents();

    return glfwWindowShouldClose(m_pWindow);
}

void CRenderer::BeginRender()
{
    m_pViewer->BeginRender();
}

void CRenderer::MainRender()
{
    m_pViewer->BeginRender();
}

void CRenderer::Render_MeshObject(IMeshObject* pMeshObj)
{
    CMeshObject* pCastedMeshObj = reinterpret_cast<CMeshObject*>(pMeshObj);
    //pCastedMeshObj->VAO()
}

void CRenderer::EndRender()
{
    m_pViewer->EndRender(m_pWindow);
}

IMeshObject* CRenderer::Create_EmptyBasicMesh(void* pData)
{
    return new CBasicMesh;
}

IMeshObject* CRenderer::Create_EmptyColoredMesh(void* pData)
{
    return nullptr;
}