#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {
    class OpenGLVertexArray: public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() {}

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) const override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) const override;

    private:
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<VertexBuffer> m_IndexBuffers;
    };
}