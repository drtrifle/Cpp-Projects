#include "hzpch.h"
#include "VertexArray.h"
#include "Renderer.h"

namespace Hazel {
    VertexArray * VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:
                HZ_CORE_ASSERT(false, "RendererAPI::None not supported!");
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexArray();
        }

        HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}