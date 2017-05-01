#include "drawer.h"
#include <QMouseEvent>

int indices[36] =
{
    0, 1, 4, 1, 4, 5, // front
    1, 3, 5, 3, 5, 7, // right
    0, 2, 4, 2, 4, 6, // left
    0, 1, 2, 1, 2, 3, // bottom
    4, 5, 6, 5, 6, 7, // top
    2, 3, 6, 3, 6, 7  // back
};


Drawer::~Drawer()
{

}

Drawer::Drawer(QWidget *parent) :
    QOpenGLWidget(parent)
{
    scene = Scene(1.0f, 3);
}



void Drawer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    program->link();
    program->bind();
    modelToWorld.setToIdentity();
    u_modelToWorld      = program->uniformLocation("modelToWorld");
    u_worldToCamera     = program->uniformLocation("worldToCamera");
    u_cameraToView      = program->uniformLocation("cameraToView");
    u_color             = program->uniformLocation("color");
    program->setUniformValue(u_modelToWorld, modelToWorld);
    program->setUniformValue(u_worldToCamera, camera.toMatrix());
    program->setUniformValue(u_cameraToView, cameraToView);


    vao.create();
    vao.bind();

    bufferForVertices = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    bufferForVertices.create();
    bufferForVertices.bind();
    bufferForVertices.setUsagePattern(QOpenGLBuffer::StaticDraw);

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);

    vao.release();
    bufferForVertices.release();
    program->release();
}

void Drawer::resizeGL(int width, int height)
{
    cameraToView.setToIdentity();
    cameraToView.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
    program->bind();
    program->setUniformValue(u_cameraToView, cameraToView);
    program->release();
    QWidget::update();
}

void Drawer::paintGL()
{
    VoxelParam voxel;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(scene.isReady())
    {
        for(int i = 0; i < scene.getXsize(); i++)
            for(int j = 0; j < scene.getYsize(); j++)
                for(int k = 0; k < scene.getZsize(); k++)
                {
                    voxel = scene.getElem(i, j, k);
                    if(voxel.isExists())
                    {
                        float length = scene.getLength();
                        QVector3D vertices[8];
                        vertices[0] = (QVector3D(i * length, j * length, k * length));
                        vertices[1] = (QVector3D((i + 1) * length, j * length, k * length));
                        vertices[2] = (QVector3D(i * length, (j + 1) * length, k * length));
                        vertices[3] = (QVector3D((i + 1) * length, (j + 1) * length, k * length));
                        vertices[4] = (QVector3D(i * length, j * length, (k + 1) * length));
                        vertices[5] = (QVector3D((i + 1) * length, j * length, (k + 1) * length));
                        vertices[6] = (QVector3D(i * length, (j + 1) * length, (k + 1) * length));
                        vertices[7] = (QVector3D((i + 1) * length, (j + 1) * length, (k + 1) * length));

                        program->bind();
                        program->setUniformValue(u_color, voxel.getColor());
                        bufferForVertices.bind();
                        bufferForVertices.allocate(vertices, sizeof(vertices));

                        vao.bind();
                        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
                        vao.release();
                        bufferForVertices.release();
                        program->release();
                    }
                }

    }
}

void Drawer::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
        camera.translateBy(cameraSpeed, camera.forward());
    if(event->key() == Qt::Key_S)
        camera.translateBy(-cameraSpeed, camera.forward());
    if(event->key() == Qt::Key_A)
        camera.translateBy(-cameraSpeed, camera.right());
    if(event->key() == Qt::Key_D)
        camera.translateBy(cameraSpeed, camera.right());
    if(event->key() == Qt::Key_Q)
        camera.translateBy(-cameraSpeed, camera.up());
    if(event->key() == Qt::Key_E)
        camera.translateBy(cameraSpeed, camera.up());

    program->bind();
    program->setUniformValue(u_worldToCamera, camera.toMatrix());
    program->release();

    QWidget::update();
}

void Drawer::mousePressEvent(QMouseEvent *pe)
{
    this->setFocus();
    pressed = true;
    ptrMousePosition = pe->pos();
}

void Drawer::mouseMoveEvent(QMouseEvent *pe)
{
    if(pressed)
    {
        camera.setRotation(
                    rotatingSpeed * (GLfloat)(pe->x() - ptrMousePosition.x()) / width(),
                    QVector3D(0.0f, 1.0f, 0.0f));
        camera.setRotation(
                    rotatingSpeed * (GLfloat)(pe->y() - ptrMousePosition.y()) / height(),
                    camera.right());
        ptrMousePosition = pe->pos();

        program->bind();
        program->setUniformValue(u_worldToCamera, camera.toMatrix());
        program->release();

        QWidget::update();
    }
}

void Drawer::mouseReleaseEvent(QMouseEvent*){
    pressed = false;
    QWidget::update();
}

void Drawer::update()
{
    QWidget::update();
}
