#include "treebuffer.h"

TreeBuffer::TreeBuffer()
{
    init();
}

void TreeBuffer::init(){
    Vertex triangle[] = {
                         Vertex{ { 0.5, 1.0, 0.0} , { 0.0, 1.0, 0.0}}, //0
                         Vertex{ { 0.0, 1.4, 0.0},{ 1.0, 0.0, 0.0}}, //1
                         Vertex{ { 0.0, 1.0, 0.5}, { 0.0, 1.0, 0.0}}, //2
                         Vertex{ { -0.5,1.0, 0.0}, { 0.0, 1.0, 0.0}}, //3
                         Vertex{ { 0.0, 1.0, -1.0}, { 0.0, 1.0, 0.0}}, //4
                         Vertex{ { 0.0, 1.0, 0.0}, { 0.3, 0.2, 0.2}}, //5
                        Vertex{ { 1.0, 0.0, 0.0}, { 0.8, 0.8, 0.0}}, //6
                        Vertex{ { 0.0, 0.0, 1.0}, { 0.8, 0.8, 0.0}}, //7
                        Vertex{ { -1.0, 0.0, 0.0}, { 0.8, 0.8, 0.0}}, //8
                        Vertex{ { 0.0, 0.0, -1.0}, { 0.8, 0.8, 0.0}}, //9
                         };

//https://www.geogebra.org/calculator <--- good pro predstavu kde maji byt body a jak jdou za sebou

    GLubyte indices[] = {
        0,1,3,4,1,2,5,7,9,5,6,8
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
