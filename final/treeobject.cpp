#include "treeobject.h"

TreeObject::TreeObject(ShaderProgram* program, VertexBuffer* buffer, Position position, Rotation rotation)
    :GraphicalObject(program, buffer, position, rotation)
{

}


void TreeObject::render(QMatrix4x4 transformationMatrix){
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

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, 0);

    // GL_TRIANGLES -- bere vzdy 3 body pro trojuhelniky jak jsou za sebou
    // GL_TRIANGLE_STRIP -- bere prvni 3 a pro kazdy dalsi trojuhelnik reusuje predchozi 1 vrchol
    // GL_TRIANGLE_FAN -- bere prvni 3 a pro kazdy dalsi trojuhelnik reusuje posledni 2 vrcholy

    program->disableAttributeArray(posAttr);
    program->disableAttributeArray(colAttr);
    program->release();

}
