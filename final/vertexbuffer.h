#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QOpenGLBuffer>
#include "Vertex.h"

class VertexBuffer
{
protected:
    QOpenGLBuffer m_buffer;
    QOpenGLBuffer m_indicesBuffer;
    QOpenGLBuffer m_colorBuffer;

public:
    VertexBuffer();
    virtual void init() = 0;
    void bind();
};

#endif // VERTEXBUFFER_H
