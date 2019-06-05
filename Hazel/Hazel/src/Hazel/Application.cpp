#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <glad/glad.h>

#include "Input.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Hazel {

    //Singleton
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
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

            //Go through each layer and render ImGui
            m_ImGuiLayer->Begin();     
            for (Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowsClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }
}
