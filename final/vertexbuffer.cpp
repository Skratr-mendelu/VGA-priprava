#include "vertexbuffer.h"

VertexBuffer::VertexBuffer():m_buffer(QOpenGLBuffer::VertexBuffer) ,m_indicesBuffer(QOpenGLBuffer::IndexBuffer){
}

void VertexBuffer::bind(){
    m_buffer.bind();
    m_indicesBuffer.bind();
}
