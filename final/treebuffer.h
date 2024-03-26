#ifndef TREEBUFFER_H
#define TREEBUFFER_H

#include "vertexbuffer.h"

class TreeBuffer: public VertexBuffer
{
public:
    TreeBuffer();
    void init() override;
};

#endif // TREEBUFFER_H
