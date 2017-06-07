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

QVector3D mix(QVector3D a, QVector3D b, float value)
{
    return (1.0f - value) * a + value * b;
}

QVector3D mix(QVector3D a, QVector3D b, QVector3D c)
{
    return (a + b + c) / 3.0;
}

Drawer::~Drawer()
{

}

Drawer::Drawer(QWidget *parent) :
    QOpenGLWidget(parent)
{
    int LengthX, LengthY, LengthZ, Step;
    //Need to implement input from file
    LengthX=3;
    LengthY=3;
    LengthZ=3;
    Step=1;

    QLCDNumber *lcdX = new QLCDNumber(2);
    lcdX->setSegmentStyle(QLCDNumber::Filled);
//    lcdX->setGeometry(200, 200, 200, 200);


    QSlider *sliderX = new QSlider(Qt::Horizontal);
    sliderX->setRange(0, LengthX);
    sliderX->setValue(LengthX);



    connect(sliderX, SIGNAL(valueChanged(int)),
                lcdX, SLOT(display(int)));
    connect(sliderX, SIGNAL(valueChanged(int)),
                this, SIGNAL(valueChanged(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lcdX);
    layout->addWidget(sliderX);
    setLayout(layout);









    float lenght = (float)Step;
    int NodeSizeX, NodeSizeY, NodeSizeZ;
    NodeSizeX = LengthX/Step;
    NodeSizeY = LengthY/Step;
    NodeSizeZ = LengthZ/Step;
    scene = Scene(lenght, NodeSizeX, NodeSizeY, NodeSizeZ);
//    scene = Scene(1, 3, 3, 3);
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

    bufferForNormals = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    bufferForNormals.create();
    bufferForNormals.bind();
    bufferForNormals.setUsagePattern(QOpenGLBuffer::StaticDraw);

    program->enableAttributeArray(1);
    program->setAttributeBuffer(1, GL_FLOAT, 0, 3, 0);

    vao.release();
    bufferForVertices.release();
    bufferForNormals.release();
    program->release();
}

void Drawer::resizeGL(int width, int height)
{
    cameraToView.setToIdentity();
    cameraToView.perspective(45.0f, width / float(height), 0.0f, 10000000000000.0f);
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

                        vertices[0] = QVector3D(i * length, j * length, k * length);
                        vertices[1] = QVector3D((i + 1) * length, j * length, k * length);
                        vertices[2] = QVector3D(i * length, (j + 1) * length, k * length);
                        vertices[3] = QVector3D((i + 1) * length, (j + 1) * length, k * length);
                        vertices[4] = QVector3D(i * length, j * length, (k + 1) * length);
                        vertices[5] = QVector3D((i + 1) * length, j * length, (k + 1) * length);
                        vertices[6] = QVector3D(i * length, (j + 1) * length, (k + 1) * length);
                        vertices[7] = QVector3D((i + 1) * length, (j + 1) * length, (k + 1) * length);

                        QVector3D base[6];

                        base[0] = QVector3D(-1.0f, 0.0f, 0.0f);
                        base[1] = QVector3D(1.0f, 0.0f, 0.0f);
                        base[2] = QVector3D(0.0f, -1.0f, 0.0f);
                        base[3] = QVector3D(0.0f, 1.0f, 0.0f);
                        base[4] = QVector3D(0.0f, 0.0f, -1.0f);
                        base[5] = QVector3D(0.0f, 0.0f, 1.0f);

                        QVector3D normal[8];
                        for(int kk = 0; kk < 2; kk++)
                            for(int jj = 0; jj < 2; jj++)
                                for(int ii = 0; ii < 2; ii++)
                                {
                                    QVector3D x = mix(base[0], base[1], (float)(i + ii)  / (float)scene.getXsize());
                                    QVector3D y = mix(base[2], base[3], (float)(j + jj) / (float)scene.getYsize());
                                    QVector3D z = mix(base[4], base[5], (float)(k + kk) / (float)scene.getZsize());
                                    normal[ii + jj * 2 + kk * 4] = mix(x, y, z);
                                }

                        program->bind();
                        program->setUniformValue(u_color, voxel.getColor());
                        bufferForVertices.bind();
                        bufferForVertices.allocate(vertices, sizeof(vertices));
                        bufferForNormals.bind();
                        bufferForNormals.allocate(normal, sizeof(normal));

                        vao.bind();
                        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
                        vao.release();
                        bufferForVertices.release();
                        bufferForNormals.release();
                        program->release();
                    }
                }

    }
}

void Drawer::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
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
        camera.rotateX(rotatingSpeed * (GLfloat)(pe->x() - ptrMousePosition.x()) / width());
        camera.rotateY(rotatingSpeed * (GLfloat)(pe->y() - ptrMousePosition.y()) / height());
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

void Drawer::wheelEvent(QWheelEvent *pe)
{
    if(pe->delta() < 0.0f)
        camera.zoomIn();
    else camera.zoomOut();
    program->bind();
    program->setUniformValue(u_worldToCamera, camera.toMatrix());
    program->release();
    QWidget::update();
}

void Drawer::update()
{
    QWidget::update();
}
