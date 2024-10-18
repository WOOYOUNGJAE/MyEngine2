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

    // Create Manager
    m_pShaderManager = new CShaderManager();
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


    glfwPollEvents();


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
