#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <glad/glad.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Hazel {
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application() {
    }

    //Whenever a Window has an event, it will call this method
    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowsClose));

        //Go through the layer stack from the back and update
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(e);

            //Stop if event handled already by some layer / overlay
            if (e.Handled) {
                break;
            }
        }
    }

    void Application::Run() {
        while (m_Running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
           
            //Go through each layer and update
            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }
            
            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    bool Application::OnWindowsClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }
}
