#pragma once

#include "Hazel/Layer.h"

namespace Hazel {
    class HAZEL_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnEvent(Event& event);
    private:
        float m_Time = 0.0f;
    };
}