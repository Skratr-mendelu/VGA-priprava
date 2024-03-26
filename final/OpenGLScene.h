/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QtCore/QRunnable>
#include "graphicalobject.h"
#include "spaceshipbuffer.h"
#include "shaderprogram.h"
#include "cubeobject.h"
#include "cubebuffer.h"
#include "spaceshipbuffer.h"
#include "spaceshipobject.h"
#include "treeobject.h"
#include <TreeBuffer.h>

#include "Vertex.h"

class OpenGLSceneRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLSceneRenderer() : m_t(0), m_Side(0) { }
    ~OpenGLSceneRenderer();

    void setT(qreal t) { m_t = t; }
    void setSide(qreal moveSide) { m_Side = moveSide; moveCameraX = moveSide; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

public slots:
    void init();
    void paint();

private:
    QSize m_viewportSize;
    QQuickWindow *m_window;

    qreal m_t;
    qreal m_Side;
    float moveCameraX;

    std::vector<GraphicalObject*> m_objects;
    std::vector<GraphicalObject*> m_SaTociObjects;
    std::vector<GraphicalObject*> m_StojiObjects;

    void clear();
};

class OpenGLScene : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
    Q_PROPERTY(qreal moveSide READ moveSide WRITE setSide NOTIFY moveSideChanged)
    QML_ELEMENT

public:
    OpenGLScene();

    qreal t() const { return m_t; }
    qreal moveSide() const { return m_Side; }
    void setT(qreal t);
    void setSide(qreal moveSide);
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void tChanged();
    void moveSideChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    void releaseResources() override;

    qreal m_t;
    qreal m_Side;

    OpenGLSceneRenderer *m_renderer;
};

#endif // OPENGLSCENE_H
