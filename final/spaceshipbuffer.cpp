#include "spaceshipbuffer.h"

SpaceShipBuffer::SpaceShipBuffer(const QVector3D& color)
    : m_color(color) // Inicializujeme barvu objektu
{
    init();
}

void SpaceShipBuffer::init(){
    Vertex triangle[] = {
        Vertex{ { 0.0, 0.0, 0.5} , { m_color.x(), m_color.y(), m_color.z()}},
        Vertex{ { 0.5, 0.25, -0.5}, { m_color.x(), m_color.y(), m_color.z()}},
        Vertex{ {-0.5, 0.25, -0.5}, { m_color.x(), m_color.y(), m_color.z()}},
        Vertex{ { 0.5,-0.25, -0.5}, { m_color.x(), m_color.y(), m_color.z()}},
        Vertex{ {-0.5,-0.25, -0.5}, { m_color.x(), m_color.y(), m_color.z()}},
       };

    GLubyte indices[] = {
        0, 1, 2, 4, 3, 1
    };

    m_buffer.create();
    m_buffer.setUsagePattern( QOpenGLBuffer::StreamDraw );
    m_buffer.bind();
    m_buffer.allocate( triangle, sizeof(triangle) );

    m_indicesBuffer.create();
    m_indicesBuffer.setUsagePattern( QOpenGLBuffer::StreamDraw );
    m_indicesBuffer.bind();
    m_indicesBuffer.allocate( indices, sizeof(indices) );
}
