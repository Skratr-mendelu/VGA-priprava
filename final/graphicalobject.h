#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include "shaderprogram.h"
#include "vertexbuffer.h"
#include "position.h"
#include "rotation.h"
#include "color.h"

class GraphicalObject
{
protected:
    ShaderProgram* m_program;
    VertexBuffer* m_buffer;
    Position m_position;
    Rotation m_rotation;
public:
    GraphicalObject(ShaderProgram* program, VertexBuffer* buffer, Position position,  Rotation rotation);
    virtual void render(QMatrix4x4 transformationMatrix) = 0;
    Position getPosition(){ return m_position; }
    Rotation getRotation(){ return m_rotation; }
};

#endif // GRAPHICALOBJECT_H
