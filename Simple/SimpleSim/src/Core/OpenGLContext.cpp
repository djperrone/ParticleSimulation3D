#include "OpenGLContext.h"

#include <iostream>
#include <string>

#include <spdlog/spdlog.h>

OpenGLContext* OpenGLContext::GLFWCallbackWrapper::s_Application = nullptr;



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


OpenGLContext::OpenGLContext(Camera& camera)
    : m_Camera(camera)
{
    Init();
    m_LastX = GetWindow().Width / 2.0f;
    m_LastY = GetWindow().Height / 2.0f;
}

OpenGLContext::~OpenGLContext()
{
    glfwTerminate();
}

void OpenGLContext::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window.Window = glfwCreateWindow(m_Window.Width, m_Window.Height, "LearnOpenGL", NULL, NULL);
    if (m_Window.Window == NULL)
    {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();

        exit(0);
    }
    glfwMakeContextCurrent(m_Window.Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(0);
    }

    glViewport(0, 0, m_Window.Width, m_Window.Height);
    

    SetCallBackFunctions();
    
    glfwSetInputMode(m_Window.Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //glfwSetInputMode(m_Window.Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);
    spdlog::info("{0}", glGetString(GL_VERSION));
}

void OpenGLContext::Run()
{   
    //InitGLFW();  
   
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);    
   

    //while (!glfwWindowShouldClose(m_Window.Window))
    //{
    //    float currentFrame = glfwGetTime();
    //    m_DeltaTime = currentFrame - m_LastFrame;
    //    m_LastFrame = currentFrame;       
    //    HandleInput();
    //    //Render();      
    //}

    //glfwTerminate();
}

void OpenGLContext::HandleInput(float dt)
{
    glfwPollEvents();
    ProcessInput(dt);
}

void OpenGLContext::SwapBuffers()
{
    // to renderer
   /* glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/

   
   

     
  
    glfwSwapBuffers(m_Window.Window);
}

bool OpenGLContext::IsRunning() const
{
    return !glfwWindowShouldClose(m_Window.Window);
}



void OpenGLContext::ProcessInput(float dt)
{


    if (glfwGetKey(m_Window.Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window.Window, true);   

    if (glfwGetKey(m_Window.Window, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera.ProcessKeyBoard(CameraMovement::FORWARD, dt);
               
    if (glfwGetKey(m_Window.Window, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera.ProcessKeyBoard(CameraMovement::BACKWARD, dt);

    if (glfwGetKey(m_Window.Window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera.ProcessKeyBoard(CameraMovement::LEFT, dt);

    if (glfwGetKey(m_Window.Window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera.ProcessKeyBoard(CameraMovement::RIGHT, dt);

    if (glfwGetKey(m_Window.Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && !m_LeftCtrlPressed)
    {
        m_ShowMouse = !m_ShowMouse;
        m_LeftCtrlPressed = true;
        
    }

    if (glfwGetKey(m_Window.Window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE && m_LeftCtrlPressed)
    {
       // m_ShowMouse = !m_ShowMouse;        
        m_LeftCtrlPressed = false;
        /*if (m_ShowMouse)
        {
            glfwSetInputMode(m_Window.Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
           
        }
        else
        {
            glfwSetInputMode(m_Window.Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
           
        }*/

    }

    if (m_ShowMouse)
    {
        glfwSetInputMode(m_Window.Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    }
    else
    {
        glfwSetInputMode(m_Window.Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }



  


        

}
void OpenGLContext::SetCallBackFunctions()
{
    GLFWCallbackWrapper::SetApplication(this);
    glfwSetCursorPosCallback(m_Window.Window, GLFWCallbackWrapper::MousePositionCallback);
    glfwSetScrollCallback(m_Window.Window, GLFWCallbackWrapper::MouseScrollCallBack);
    glfwSetFramebufferSizeCallback(m_Window.Window, GLFWCallbackWrapper::WindowResizeCallBack);    
}

void OpenGLContext::GLFWCallbackWrapper::WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
    s_Application->WindowResizeCallBack(window, width, height);
}

void OpenGLContext::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{   
    if (s_Application->m_FirstMouse)
    {
        s_Application->m_LastX = xpos;
        s_Application->m_LastY = ypos;
        s_Application->m_FirstMouse = false;
    }
    float xOffset = xpos - s_Application->m_LastX;
    float yOffset = s_Application->m_LastY - ypos;
    s_Application->m_LastX = xpos;
    s_Application->m_LastY = ypos;
   
    s_Application->MousePositionCallback(window, xOffset, yOffset);  
}

void OpenGLContext::GLFWCallbackWrapper::MouseScrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
{    
    s_Application->MouseScrollCallBack(window, xOffset, yOffset);
}

void OpenGLContext::GLFWCallbackWrapper::SetApplication(OpenGLContext* application)
{
    GLFWCallbackWrapper::s_Application = application;
}

void OpenGLContext::MousePositionCallback(GLFWwindow* window, double positionX, double positionY)
{
    if (!m_ShowMouse)
    m_Camera.ProcessMouseMovement(positionX, positionY);
}

void OpenGLContext::WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    m_Window.Width = width;
    m_Window.Height = height;
}

void OpenGLContext::MouseScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
   // if (!m_ShowMouse)
   m_Camera.ProcessMouseScroll(yoffset);
}


//void OpenGLContext::InitGLFW()
//{
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    m_Window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//    if (m_Window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//
//        exit(0);
//    }
//    glfwMakeContextCurrent(m_Window);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        exit(0);
//    }
//
//    glViewport(0, 0, 800, 600);
//    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
//        {
//            glViewport(0, 0, width, height);
//
//        });
//
//    SetCallBackFunction();
//    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//}
