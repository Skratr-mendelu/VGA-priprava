#include "cubeobject.h"
#include <QOpenGLFunctions>

CubeObject::CubeObject(ShaderProgram* program, VertexBuffer* buffer, Position position, Rotation rotation)
    :GraphicalObject(program, buffer, position, rotation)
{

}


void CubeObject::render(QMatrix4x4 transformationMatrix){
    QOpenGLShaderProgram* program = m_program->getProgram();
    GLuint colAttr = m_program->getColAttr();
    GLuint posAttr = m_program->getPosAttr();
    GLuint matrix = m_program->getMatrix();

    program->bind();
    program->enableAttributeArray(posAttr);
    program->enableAttributeArray(colAttr);

    program->setUniformValue(matrix, transformationMatrix);


    m_buffer->bind(); // do not forget!

    program->setAttributeBuffer(posAttr, GL_FLOAT, 0, 3, sizeof(Vertex));
    program->setAttributeBuffer(colAttr, GL_FLOAT, sizeof(Vertex::position), 3, sizeof(Vertex));

    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_BYTE, 0);	// front, top, rear, bottom
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void*)(10*sizeof(GLubyte)) ); // right
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (void*)(14*sizeof(GLubyte)) ); // left

    program->disableAttributeArray(posAttr);
    program->disableAttributeArray(colAttr);
    program->release();

}
