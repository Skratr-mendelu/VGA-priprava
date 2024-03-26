#include "graphicalobject.h"

GraphicalObject::GraphicalObject(ShaderProgram* program, VertexBuffer* buffer, Position position, Rotation rotation){
    m_program = program;
    m_buffer = buffer;
    m_position = position;
    m_rotation = rotation;
}

/*
void GraphicalObject::render(QMatrix4x4 transformationMatrix){
    QOpenGLShaderProgram* program = m_program->getProgram();
    GLuint colAttr = m_program->getColAttr();
    GLuint posAttr = m_program->getPosAttr();
    GLuint matrixId = m_program->getMatrix();

    program->bind();
    program->enableAttributeArray(posAttr);
    program->enableAttributeArray(colAttr);

    m_buffer->bind(); // do not forget!

    program->setUniformValue(matrixId, transformationMatrix);

    program->setAttributeBuffer(posAttr, GL_FLOAT, 0, 2, sizeof(Vertex));
    program->setAttributeBuffer(colAttr, GL_FLOAT, sizeof(Vertex::position), 3, sizeof(Vertex));

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);

    program->disableAttributeArray(posAttr);
    program->disableAttributeArray(colAttr);
    program->release();

}
*/
