#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
        : m_WindowHandle(windowHandle)
    {
        HZ_CORE_ASSERT(m_WindowHandle, "Window Handle is Null!");
    }

    void OpenGLContext::Init() {        
        //Glad Stuff
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        HZ_CORE_ASSERT(status, "Could not initialize Glad!");
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}