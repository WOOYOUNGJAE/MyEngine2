#include "pch.h"
#include "Renderer.h"

#include "BasicMesh.h"
#include "Viewer.h"
#include "ShaderManager.h"
#include "enums.h"
#include "Util_Funcs.h"

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

CRenderer::CRenderer(IRenderer::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle, GLFWwindow ** ppOutGLWin)
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

    // Create Manager
    m_pShaderManager = new CShaderManager();

    *ppOutGLWin = m_pWindow;
}

CRenderer::~CRenderer()
{
    RELEASE_INSTANCE(m_pShaderManager);
    DELETE_INSTANCE(m_pViewer);
}

void CRenderer::Initialize(void*)
{
    m_pShaderManager->Load_Shader(Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::SIMPLE, "Simple");
}

int32 CRenderer::MainRender(FLOAT fDeltaTime)
{

    if (m_pViewer == nullptr)
    {
        ERROR_BOX("Viewer is Null");
        __debugbreak();
        return FALSE;
    }

    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_pWindow, TRUE);
        glfwTerminate();
        return FALSE;
    }
    for (UINT eShaderType = 0; eShaderType < Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::NUM; ++eShaderType)
    {
        GLuint curShaderProgram = m_pShaderManager->m_ShaderPrograms[eShaderType];
        glUseProgram(curShaderProgram); // Bind Shader Program
        
        if (eShaderType == Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::SIMPLE)
        {
            GLuint uniformViewProj = glGetUniformLocation(curShaderProgram, "g_ViewProj");
            glUniformMatrix4fv(uniformViewProj, 1, GL_TRUE/*row to col*/, glm::value_ptr(m_matViewProj));
        }

        for (auto& iterMeshObj : m_RenderQueueArr[eShaderType])
        {
            glBindVertexArray(iterMeshObj->VAO()); // Bind VAO
            glDrawElements(GL_TRIANGLES, (GLsizei)iterMeshObj->NumIndices(), GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0); // Unbind VAO

            
            GLuint uniformModel = glGetUniformLocation(curShaderProgram, "g_Model");
            glm::mat4x4 curModelMatrix{};
            memcpy_s(&curModelMatrix, sizeof(mat4x4), &iterMeshObj->WorldMat(), sizeof(XMFLOAT4X4));

            //glUniformMatrix4fv(uniformModel, 1, GL_TRUE/*row to col*/, glm::value_ptr(curModelMatrix));
            glUniformMatrix4fv(uniformModel, 1, GL_FALSE/*row to col*/, glm::value_ptr(curModelMatrix));


            CHECK_GL_ERROR
        }
        m_RenderQueueArr[eShaderType].clear();
    }


    return !glfwWindowShouldClose(m_pWindow);
}

void CRenderer::Update_CameraInfo(XMFLOAT4X4& matCameraWorld, CAMERA_DESC& cameraDesc)
{
    ::Convert_Matrix_DXtoGL(matCameraWorld);

    memcpy_s(&m_matCameraWorld, sizeof(mat4x4), &matCameraWorld, sizeof(XMFLOAT4X4));
    
    m_matView = glm::inverse(m_matCameraWorld);
    m_matProj = glm::perspectiveLH(cameraDesc.fFovY, cameraDesc.fAspectRatio, cameraDesc.fNear, cameraDesc.fFar);
    m_matViewProj = m_matView * m_matProj;


}

void CRenderer::BeginRender()
{
    glfwPollEvents();

    // Update Key Inputs
    m_KeyManager.Update_KeyStates(m_pWindow);


    m_pViewer->BeginRender();
}

void CRenderer::Render_MeshObject_External(IMeshObject* pMeshObj, XMFLOAT4X4& matWorld)
{
    CMeshObject* pCastedMeshObj = static_cast<CMeshObject*>(pMeshObj);
    ::Convert_Matrix_DXtoGL(matWorld);
    pCastedMeshObj->Set_WorldMat(matWorld);
    m_RenderQueueArr[pCastedMeshObj->ShaderType()].push_back(pCastedMeshObj);
}

void CRenderer::MainRender()
{
    //for (UINT eShaderType = 0; eShaderType < Renderer_OpenGL::GL_SHADER_PROGRAM_TYPE::NUM; ++eShaderType)
    //{
    //    GLuint curShaderProgram = m_pShaderManager->m_ShaderPrograms[eShaderType];
    //    glUseProgram(curShaderProgram); // Bind Shader Program
    //    for (auto& iterMeshObj : m_RenderQueueArr[eShaderType])
    //    {
    //        glBindVertexArray(iterMeshObj->VAO()); // Bind VAO
    //        glDrawElements(GL_TRIANGLES, iterMeshObj->NumIndices(), GL_UNSIGNED_INT, nullptr);
    //        glBindVertexArray(0); // Unbind VAO
    //    }
    //    m_RenderQueueArr[eShaderType].clear();
    //}
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

void CRenderer::GLFW_KeyManager::Update_KeyStates(GLFWwindow* pWin)
{
    for (INT keyChecking = 0; keyChecking < VK_MAX; ++keyChecking)
    {
        int glfwKey = ConvertVkToGlfwKey(keyChecking);
        int glfwState = glfwGetKey(pWin, glfwKey);
        if (glfwState)
        {
            int a = 1;
        }
        if (glfwState == GLFW_PRESS || glfwState == GLFW_REPEAT) // If Pressed
        {
            if (m_keyStateArr[keyChecking].first) // and Also Pressed Before
            {
                m_keyStateArr[keyChecking].second = KEY_PRESSING; // Pressing
            }
            else
            {
                m_keyStateArr[keyChecking].first = true;
                m_keyStateArr[keyChecking].second = KEY_DOWN; // Pressed this tick
            }
        }
        else if (glfwState == GLFW_RELEASE) // Not Pressed
        {
            if (m_keyStateArr[keyChecking].first) // but Pressed Before
            {
                m_keyStateArr[keyChecking].first = false;
                m_keyStateArr[keyChecking].second = KEY_UP;
            }
            else
            {
                m_keyStateArr[keyChecking].second = KEY_NONE;
            }
        }
    }
}

bool CRenderer::GLFW_KeyManager::Key_Pressing(int inKey)
{
    return m_keyStateArr[inKey].second == KEY_PRESSING;
}

bool CRenderer::GLFW_KeyManager::Key_Down(int inKey)
{
    return m_keyStateArr[inKey].second == KEY_DOWN;
}

bool CRenderer::GLFW_KeyManager::Key_Up(int inKey)
{
    return m_keyStateArr[inKey].second == KEY_UP;
}

int CRenderer::GLFW_KeyManager::ConvertVkToGlfwKey(int vkKey)
{
    switch (vkKey)
    {
    case 0x01: return GLFW_MOUSE_BUTTON_LEFT;
    case 0x02: return GLFW_MOUSE_BUTTON_RIGHT;
    case 0x04: return GLFW_MOUSE_BUTTON_MIDDLE;
    case 0x08: return GLFW_KEY_BACKSPACE;
    case 0x09: return GLFW_KEY_TAB;
    case 0x0D: return GLFW_KEY_ENTER;
    case 0x10: return GLFW_KEY_LEFT_SHIFT;
    case 0x11: return GLFW_KEY_LEFT_CONTROL;
    case 0x12: return GLFW_KEY_LEFT_ALT;
    case 0x1B: return GLFW_KEY_ESCAPE;
    case 0x20: return GLFW_KEY_SPACE;
    case 0x21: return GLFW_KEY_PAGE_UP;
    case 0x22: return GLFW_KEY_PAGE_DOWN;
    case 0x23: return GLFW_KEY_END;
    case 0x24: return GLFW_KEY_HOME;
    case 0x25: return GLFW_KEY_LEFT;
    case 0x26: return GLFW_KEY_UP;
    case 0x27: return GLFW_KEY_RIGHT;
    case 0x28: return GLFW_KEY_DOWN;
    case 0x2C: return GLFW_KEY_PRINT_SCREEN;
    case 0x2D: return GLFW_KEY_INSERT;
    case 0x2E: return GLFW_KEY_DELETE;
    case 0x5B: return GLFW_KEY_LEFT_SUPER;  // Left Windows key
    case 0x5C: return GLFW_KEY_RIGHT_SUPER; // Right Windows key
    case 0x60: return GLFW_KEY_KP_0;
    case 0x61: return GLFW_KEY_KP_1;
    case 0x62: return GLFW_KEY_KP_2;
    case 0x63: return GLFW_KEY_KP_3;
    case 0x64: return GLFW_KEY_KP_4;
    case 0x65: return GLFW_KEY_KP_5;
    case 0x66: return GLFW_KEY_KP_6;
    case 0x67: return GLFW_KEY_KP_7;
    case 0x68: return GLFW_KEY_KP_8;
    case 0x69: return GLFW_KEY_KP_9;
    case 0x6A: return GLFW_KEY_KP_MULTIPLY;
    case 0x6B: return GLFW_KEY_KP_ADD;
    case 0x6D: return GLFW_KEY_KP_SUBTRACT;
    case 0x6E: return GLFW_KEY_KP_DECIMAL;
    case 0x6F: return GLFW_KEY_KP_DIVIDE;
    case 0x70: return GLFW_KEY_F1;
    case 0x71: return GLFW_KEY_F2;
    case 0x72: return GLFW_KEY_F3;
    case 0x73: return GLFW_KEY_F4;
    case 0x74: return GLFW_KEY_F5;
    case 0x75: return GLFW_KEY_F6;
    case 0x76: return GLFW_KEY_F7;
    case 0x77: return GLFW_KEY_F8;
    case 0x78: return GLFW_KEY_F9;
    case 0x79: return GLFW_KEY_F10;
    case 0x7A: return GLFW_KEY_F11;
    case 0x7B: return GLFW_KEY_F12;
    case 0x90: return GLFW_KEY_NUM_LOCK;
    case 0x91: return GLFW_KEY_SCROLL_LOCK;

        /*
        * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
        * 0x3A - 0x40 : unassigned
        * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
        */
    default: return vkKey; // ASCII
    }
}
