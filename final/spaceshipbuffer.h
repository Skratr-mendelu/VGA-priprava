#ifndef SPACESHIPBUFFER_H
#define SPACESHIPBUFFER_H

#include "qvectornd.h"
#include "vertexbuffer.h"

class SpaceShipBuffer: public VertexBuffer
{
public:
    SpaceShipBuffer(const QVector3D& color);
    void init() override;

private:
    QVector3D m_color;
};

#endif // SPACESHIPBUFFER_H
