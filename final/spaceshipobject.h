#ifndef SPACESHIPOBJECT_H
#define SPACESHIPOBJECT_H

#include "graphicalobject.h"

class SpaceshipObject : public GraphicalObject
{
public:
    SpaceshipObject(ShaderProgram* program, VertexBuffer* buffer, Position position, Rotation rotation);
    void render(QMatrix4x4 transformationMatrix) override;
};

#endif // SPACESHIPOBJECT_H
