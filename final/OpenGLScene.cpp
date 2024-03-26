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

#include "OpenGLScene.h"


OpenGLScene::OpenGLScene()
    : m_t(0)
    , m_Side(0)
    , m_renderer(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &OpenGLScene::handleWindowChanged);
}

void OpenGLScene::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void OpenGLScene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Right:
        qDebug("Key_right");
        m_Side += 1;
        if (window())
            window()->update();        // Pohyb po ose X
        break;
    case Qt::Key_Left:
        qDebug("Key_left");
        m_Side += 1;
        if (window())
            window()->update();// Pohyb po ose X
        break;
        // Případně můžete přidat další case pro další klávesy...
    }
}

void OpenGLScene::setSide(qreal moveSide)
{
    if (moveSide == m_Side)
        return;
    m_Side = moveSide;
    emit moveSideChanged();
    if (window())
        window()->update();
}

void OpenGLScene::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &OpenGLScene::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &OpenGLScene::cleanup, Qt::DirectConnection);
        // Ensure we start with cleared to black. The squircle's blend mode relies on this.
        win->setColor(Qt::black);
    }
}

void OpenGLScene::cleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
}

class CleanupJob : public QRunnable
{
public:
    CleanupJob(OpenGLSceneRenderer *renderer) : m_renderer(renderer) { }
    void run() override { delete m_renderer; }
private:
    OpenGLSceneRenderer *m_renderer;
};

void OpenGLScene::releaseResources()
{
    window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;
}

OpenGLSceneRenderer::~OpenGLSceneRenderer()
{
    //delete m_program;
}

void OpenGLScene::sync()
{
    if (!m_renderer) {
        m_renderer = new OpenGLSceneRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &OpenGLSceneRenderer::init, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &OpenGLSceneRenderer::paint, Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setSide(m_Side);
    m_renderer->setWindow(window());
}

void OpenGLSceneRenderer::init()
{
    if (m_objects.size() == 0){
        QSGRendererInterface *rif = m_window->rendererInterface();
        Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL);

        initializeOpenGLFunctions();

        //VertexBuffer* spaceShip = new SpaceShipBuffer();
        CubeBuffer* cube = new CubeBuffer();
        SpaceShipBuffer* spaceship = new SpaceShipBuffer(QVector3D(1.0, 0.0, 0.0));

        TreeBuffer* tree = new TreeBuffer();

        ShaderProgram* program = new ShaderProgram();
        m_StojiObjects.push_back(new CubeObject(program, cube,
                                           Position{-0.5, 0.0, 0.5},
                                           Rotation{30.0, {0.0, 1.0, 0.0}}
                                        ));
        // m_objects.push_back(new CubeObject(program, cube,
        //                                    Position{ 1.0, 0.0, 1.0},
        //                                    Rotation{ 45.0, {1.0, 0.0, 0.0}}
        //                                    ));s
        // m_objects.push_back(new SpaceshipObject(program, spaceship,
        //                                    Position{ 0.0, 0.0, 0.0},
        //                                    Rotation{ 0.0, {0.0, 1.0, 0.0}}
        //                                    ));

        m_objects.push_back(new TreeObject(program, tree,
                                           Position{0.0, 0.0, 2.5},
                                           Rotation{0.0, {0.0, 0.0, 0.0}}
                                           ));

        m_SaTociObjects.push_back(new TreeObject(program, tree,
                                                     Position{-3.0, 0.0, 2.0},
                                                     Rotation{0.0, {1.0, 0.0, 0.0}}
                                                     ));
        m_SaTociObjects.push_back(new TreeObject(program, tree,
                                                 Position{3.0, 0.0, 2.0},
                                                 Rotation{0.0, {0.0, 0.0, 1.0}}
                                                 ));
        m_SaTociObjects.push_back(new TreeObject(program, tree,
                                                 Position{-1.0, 0.0, -1.5},
                                                 Rotation{0.0, {0.0, 1.0, 0.0}}
                                                 ));
        m_SaTociObjects.push_back(new TreeObject(program, tree,
                                                 Position{1.0, 0.0, -1.5},
                                                 Rotation{0.0, {0.0, 1.0, 0.0}}
                                                 ));
    }
}

void OpenGLSceneRenderer::clear(){
    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void OpenGLSceneRenderer::paint()
{
    // Play nice with the RHI. Not strictly needed when the scenegraph uses OpenGL directly.
    m_window->beginExternalCommands();

    clear();

    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(90.0f, 4.0f/3.0f, 0.1f, 100.0f);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();

    modelViewMatrix.lookAt(
        {0.0,2.0,-2.0},
        {0.0, 0.0, 0.0},
        {0.0,1.0,0.0});

    // modelViewMatrix.rotate(m_t, 0.0f, 1.0f, 0.0f);
    //qDebug() << "m_t: " << m_t;

    for(auto object: m_objects){
        Rotation objRotation = object->getRotation();
        Position objPosition = object->getPosition();
        QMatrix4x4 tmpModelViewMatrix = modelViewMatrix;

        // Pokud je objekt SpaceShip, aktualizujte jeho pozici na základě hodnoty m_Side
        if (dynamic_cast<SpaceshipObject*>(object) != nullptr) {
            objPosition.x += m_Side;
        }

        if(dynamic_cast<TreeObject*>(object) != nullptr)
        {
            float angle = (objRotation.angle + m_t) * M_PI / 180.0;
            //              centr  radius
            float centerX = 0.0 + 1.5 * cos(angle);
            float centerZ = 1.0 + 1.5 * sin(angle);

            // Před rotací přeložte objekt na vypočtenou polohu bodu
            tmpModelViewMatrix.translate(centerX, objPosition.y, centerZ);
            qDebug() << "Uhel: " << m_t;
            tmpModelViewMatrix.rotate(objRotation.angle, objRotation.axis[0], objRotation.axis[1], objRotation.axis[2]);
        }
        else
        {
            tmpModelViewMatrix.rotate(objRotation.angle, objRotation.axis[0], objRotation.axis[1], objRotation.axis[2]);
            tmpModelViewMatrix.translate(objPosition.x, objPosition.y, objPosition.z);
        }

        tmpModelViewMatrix.scale(0.5, 1.0, 0.5);
        // qDebug("tst");
        object->render(projectionMatrix*tmpModelViewMatrix);
    }

    for(auto object: m_SaTociObjects){
        Rotation objRotation = object->getRotation();
        Position objPosition = object->getPosition();
        QMatrix4x4 tmpModelViewMatrix = modelViewMatrix;

        // Pokud je objekt SpaceShip, aktualizujte jeho pozici na základě hodnoty m_Side
        if (dynamic_cast<SpaceshipObject*>(object) != nullptr) {
            objPosition.x += m_Side;
        }

        if(dynamic_cast<TreeObject*>(object) != nullptr)
        {
            // float angle = (objRotation.angle + m_t) * M_PI / 180.0;

            // float centerX = 0.0 + 1.0 * cos(angle);
            // float centerZ = 0.0 + 1.0 * sin(angle);

            // // Před rotací přeložte objekt na vypočtenou polohu bodu
            // tmpModelViewMatrix.translate(centerX, objPosition.y, centerZ);
            qDebug() << "Uhel: " << m_t;
            tmpModelViewMatrix.translate(objPosition.x, objPosition.y, objPosition.z);
            tmpModelViewMatrix.rotate(objRotation.angle+m_t, objRotation.axis[0], objRotation.axis[1], objRotation.axis[2]);
        }
        else
        {
            tmpModelViewMatrix.rotate(objRotation.angle, objRotation.axis[0], objRotation.axis[1], objRotation.axis[2]);
            tmpModelViewMatrix.translate(objPosition.x, objPosition.y, objPosition.z);
        }
        tmpModelViewMatrix.scale(0.5, 0.8, 0.5);
        object->render(projectionMatrix*tmpModelViewMatrix);
    }

    for(auto object: m_StojiObjects){
        Rotation objRotation = object->getRotation();
        Position objPosition = object->getPosition();
        QMatrix4x4 tmpModelViewMatrix = modelViewMatrix;

        tmpModelViewMatrix.translate(objPosition.x, objPosition.y, objPosition.z);
        tmpModelViewMatrix.rotate(objRotation.angle, objRotation.axis[0], objRotation.axis[1], objRotation.axis[2]);

        object->render(projectionMatrix*tmpModelViewMatrix);
    }

    m_window->endExternalCommands();
}
