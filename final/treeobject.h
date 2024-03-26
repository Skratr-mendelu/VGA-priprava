#ifndef TREEOBJECT_H
#define TREEOBJECT_H

#include "graphicalobject.h"

class TreeObject : public GraphicalObject
{
public:
    TreeObject(ShaderProgram* program, VertexBuffer* buffer, Position position, Rotation rotation);
    void render(QMatrix4x4 transformationMatrix) override;
};

#endif // TREEOBJECT_H
