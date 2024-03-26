#include "shaderprogram.h"

ShaderProgram::ShaderProgram()
{
    init();
}

void ShaderProgram::init(){
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       "attribute highp vec4 posAttr;\n"
                                       "attribute lowp vec4 colAttr;\n"
                                       "varying lowp vec4 col;\n"
                                       "uniform highp mat4 matrix;\n"
                                       "void main() {\n"
                                       "   col = colAttr; \n"
                                       "   gl_Position = matrix * posAttr;\n"
                                       "}\n");
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       "varying lowp vec4 col;\n"
                                       "void main() {\n"
                                       "   gl_FragColor = col;\n"
                                       "}\n");
    m_program->link();

    m_matrix = m_program->uniformLocation("matrix");
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
}

QOpenGLShaderProgram* ShaderProgram::getProgram(){
    return m_program;
}

GLuint ShaderProgram::getPosAttr(){
    return m_posAttr;
}

GLuint ShaderProgram::getColAttr(){
    return m_colAttr;
}

GLuint ShaderProgram::getMatrix(){
    return m_matrix;
}
