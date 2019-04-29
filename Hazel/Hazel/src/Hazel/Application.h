#pragma once

#include "Core.h"
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
   private:
       bool OnWindowsClose(WindowCloseEvent& e);

       std::unique_ptr<Window> m_Window;
       bool m_Running = true;
    };

   //To be defined in CLIENT
   Application* CreateApplication();
}



