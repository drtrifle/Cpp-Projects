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

        // Vertex Array
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        // Vertex Buffer
        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
       
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        // Index Buffer
        uint32_t indices[3]{ 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    

        //Create Shader (Vert & Frag)
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            out vec3 v_Position;                    

            void main(){
                gl_Position = vec4(a_Position, 1.0);
                v_Position = a_Position;
            }
        )";
        
        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;          
            in vec3 v_Position;                    

            void main(){
                color = vec4(v_Position * .5 + .5, 1.0);
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
            glClearColor(.2f, .2f, .2f, 1);
            glClear(GL_COLOR_BUFFER_BIT);
           
            //Bind Shader
            m_Shader->Bind();

            //Draw Triangle
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
