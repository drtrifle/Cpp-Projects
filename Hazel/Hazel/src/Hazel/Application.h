#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Window.h"

namespace Hazel {
   class HAZEL_API Application {
    
    public:
        //Constructor / Destructor Stuff
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
   private:
       bool OnWindowsClose(WindowCloseEvent& e);

       std::unique_ptr<Window> m_Window;
       bool m_Running = true;
       LayerStack m_LayerStack;

       static Application* s_Instance;
    };

   //To be defined in CLIENT
   Application* CreateApplication();
}



