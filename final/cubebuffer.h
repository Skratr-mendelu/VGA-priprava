#ifndef CUBEBUFFER_H
#define CUBEBUFFER_H

#include "vertexbuffer.h"

class CubeBuffer: public VertexBuffer
{
public:
    CubeBuffer();
    void init() override;
};

#endif // CUBEBUFFER_H
