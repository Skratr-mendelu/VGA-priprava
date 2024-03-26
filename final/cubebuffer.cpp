#include "cubebuffer.h"

CubeBuffer::CubeBuffer()
{
    init();
}

void CubeBuffer::init(){    
    const GLint size = 1;

    Vertex vertices[] = {
            Vertex{ {0.0f,      0.0f,      0.0f},{ 1.0, 0.0, 0.0 } },// 0
            Vertex{ {0.0f+size, 0.0f,      0.0f},{ 0.0, 1.0, 0.0 } },// 1
            Vertex{ {0.0f+size, 0.0f+size, 0.0f},{ 0.0, 0.0, 1.0 } },// 2
            Vertex{ {0.0f,      0.0f+size, 0.0f},{ 1.0, 1.0, 0.0 } },// 3
            Vertex{ {0.0f,      0.0f,      0.0f+size},{ 1.0, 0.0, 0.0 } },// 4
            Vertex{ {0.0f+size, 0.0f,      0.0f+size},{ 0.0, 1.0, 0.0 } },// 5
            Vertex{ {0.0f+size, 0.0f+size, 0.0f+size},{ 0.0, 0.0, 1.0 } },// 6
            Vertex{ {0.0f,      0.0f+size, 0.0f+size},{ 1.0, 1.0, 0.0 } } // 7
        };

        GLubyte indices[] = {
            0, 1, 3, 2, 7, 6, 4, 5, 0, 1, // front, top, rear, bottom
            1, 5, 2, 6, // right
            0, 4, 3, 7  // left
        };

        m_buffer.create();
        m_buffer.setUsagePattern( QOpenGLBuffer::StreamDraw );
        m_buffer.bind();
        m_buffer.allocate( vertices, sizeof(vertices) );

        m_indicesBuffer.create();
        m_indicesBuffer.setUsagePattern( QOpenGLBuffer::StreamDraw );
        m_indicesBuffer.bind();
        m_indicesBuffer.allocate( indices, sizeof(indices) );
}
