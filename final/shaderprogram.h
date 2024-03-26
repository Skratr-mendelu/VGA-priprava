#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLShaderProgram>

class ShaderProgram
{
    QOpenGLShaderProgram *m_program;
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrix;
public:
    ShaderProgram();
    void init();
    QOpenGLShaderProgram* getProgram();
    GLuint getPosAttr();
    GLuint getColAttr();
    GLuint getMatrix();
};

#endif // SHADERPROGRAM_H
