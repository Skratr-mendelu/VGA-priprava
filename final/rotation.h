#ifndef ROTATION_H
#define ROTATION_H

#include <QOpenGLFunctions>

struct Rotation
{
    GLfloat angle;
    GLfloat axis[3];
};

#endif // ROTATION_H
