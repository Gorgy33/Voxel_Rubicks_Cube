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

int lineIndices[24] =
{
    0, 1 , 0, 2, 0, 4,
    1, 3, 1, 5,
    2, 3, 2, 6,
    3, 7,
    4, 5, 4, 6,
    5, 7,
    6, 7
};

int layernumber (int i, int j, int k, int Nodesize, int a, int b, int layer)
{

    if((i == a) || (i == (Nodesize -b)) || (j == a) ||  (j == (Nodesize -b)) || (k == a) ||  (k == (Nodesize -b)))
    {
        return layer;
    }
    else
    {
        a++;
        b++;
        layer++;
        return layernumber(i,j,k,Nodesize,a,b, layer);
    }
}

int sign(double x)
{
    if(x>0)
        return 1;
    else
        if(x<0)
            return -1;
        else
            return 0;
}

QVector3D mix(QVector3D a, QVector3D b, float value)
{
    return (1.0f - value) * a + value * b;
}

QVector3D mix(QVector3D a, QVector3D b, QVector3D c)
{
    return (a + b + c) / 3.0;
}




void Drawer:: setCollor(int x,int y,int z)
{
    matrix.resize(x);
    for(int i = 0; i < x; ++i)
    {
        matrix[i].resize(y);
        for(int j = 0; j < y; j++)
            matrix[i][j].resize(z);
    }


    sizeX = x;
    sizeY = y;
    sizeZ = z;

    float r,g,b;

    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            for(int k = 0; k < z; k++)
            {
                QVector3D color;
                r = rand()%256;
                r = r/255;
                g = rand()%256;
                g = g/255;
                b = rand()%256;
                b = b/255;

                //    double value;
                //    double red, blue, yellow, green, minblue, rad, rad0;
                //    int layernum;
                //    rad0=NodesizeX/2.0;
                //    minblue = 0;
                //    red = (sign(rad0-(length/2))*log(rad0-(length/2)))/(4*M_PI)  ;
                //    blue = minblue + (red - minblue) / 4;
                //    yellow = red - (red - minblue) / 4;
                //    green = minblue + (red - minblue) / 2;



                color = QVector3D(r, g, b);

                matrix[i][j][k].setColor(color);
            }

}

void Drawer:: setExist(int x, int y, int z)
{
        for(int i = 0; i < x; ++i)
            for(int j = 0; j < y; ++j)
                for(int k = 0; k < z; ++k)
                {

                    if((i == 0) || (i == (x -1)) || (j == 0) ||  (j == (y -1)) || (k == 0) ||  (k == (z -1)))
                        matrix[i][j][k].setExists(true);
                    else
                        matrix[i][j][k].setExists(false);
                }
}

void Drawer::MoleMoveForward(int direction)
{
    Zdirection  = Zdirection + direction;
    scene = Scene();
    QWidget::update();
}

void Drawer::MoleMoveRight(int direction)
{
    Xdirection  = Xdirection + direction;
    scene = Scene();
    QWidget::update();
}

void Drawer::MoleMoveUp(int direction)
{
    Ydirection  = Ydirection + direction;
    scene = Scene();
    QWidget::update();
}



Drawer::~Drawer()
{

}



Drawer::Drawer(QWidget *parent) :
    QOpenGLWidget(parent)
{
    float LengthX, LengthY, LengthZ, Step;
    //Need to implement input from file
    LengthX=3.0;
    LengthY=3.0;
    LengthZ=3.0;
    Step=0.1;


    int NodeSizeX, NodeSizeY, NodeSizeZ;
    NodeSizeX = LengthX/Step;
    NodeSizeY = LengthY/Step;
    NodeSizeZ = LengthZ/Step;


    QLCDNumber *lcdX = new QLCDNumber(4, parent);
    lcdX->setSegmentStyle(QLCDNumber::Filled);
    lcdX->setGeometry(930, 20, 50, 30);
    lcdX->display(NodeSizeX);
    QLCDNumber *lcdY = new QLCDNumber(4, parent);
    lcdY->setSegmentStyle(QLCDNumber::Filled);
    lcdY->setGeometry(930, 120, 50, 30);
    lcdY->display(NodeSizeY);
    QLCDNumber *lcdZ = new QLCDNumber(4, parent);
    lcdZ->setSegmentStyle(QLCDNumber::Filled);
    lcdZ->setGeometry(930, 220, 50, 30);
    lcdZ->display(NodeSizeZ);


    QSlider *sliderX = new QSlider(Qt::Horizontal, parent);
    sliderX->setRange(0, NodeSizeX);
    sliderX->setValue(NodeSizeX);
    sliderX->setGeometry(900, 60, 120, 20);
    QSlider *sliderY = new QSlider(Qt::Horizontal, parent);
    sliderY->setRange(0, NodeSizeY);
    sliderY->setValue(NodeSizeY);
    sliderY->setGeometry(900, 160, 120, 20);
    QSlider *sliderZ = new QSlider(Qt::Horizontal, parent);
    sliderZ->setRange(0, NodeSizeZ);
    sliderZ->setValue(NodeSizeZ);
    sliderZ->setGeometry(900, 260, 120, 20);

    QCheckBox *GridLine = new QCheckBox(tr("Show grid line"),parent);
    GridLine->setGeometry(900, 500, 120, 50);

    QCheckBox *Mole = new QCheckBox(tr("Mole"), parent);
    Mole->setGeometry(900, 350, 120, 50);

    QCheckBox *LockCamera = new QCheckBox(tr("Lock Camera"),parent);
    LockCamera->setGeometry(900, 450, 120, 50);




    QLCDNumber *lcdMole = new QLCDNumber(2, parent);
    lcdMole->setSegmentStyle(QLCDNumber::Filled);
    lcdMole->setGeometry(900, 300, 50, 30);
    lcdMole->display(0);


    connect(sliderX, SIGNAL(valueChanged(int)),
                lcdX, SLOT(display(int)));

    connect(sliderY, SIGNAL(valueChanged(int)),
                lcdY, SLOT(display(int)));

    connect(sliderZ, SIGNAL(valueChanged(int)),
                lcdZ, SLOT(display(int)));





    connect(GridLine, SIGNAL(stateChanged(int)),
                this, SLOT(paintGrid(int)));
    connect(LockCamera, SIGNAL(stateChanged(int)),
                this, SLOT(CameraCenter(int)));


    connect(sliderX, SIGNAL(valueChanged(int)), this, SLOT(DeleteLayerX(int)));
    connect(sliderY, SIGNAL(valueChanged(int)), this, SLOT(DeleteLayerY(int)));
    connect(sliderZ, SIGNAL(valueChanged(int)), this, SLOT(DeleteLayerZ(int)));

    connect(Mole, SIGNAL(stateChanged(int)), this, SLOT(DrawMole(int)));
    connect(Mole, SIGNAL(stateChanged(int)), lcdMole, SLOT(display(int)));

    sideLength = Step;

    setCollor(NodeSizeX, NodeSizeY, NodeSizeZ);
    setExist(NodeSizeX, NodeSizeY, NodeSizeZ);

    scene = Scene();

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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(scene.isReady())
    {
        QVector3D black = QVector3D (0.0f, 0.0f, 0.0f);

        for(int i = 0; i < getXsize(); i++)
            for(int j = 0; j < getYsize(); j++)
                for(int k = 0; k < getZsize(); k++)
                {


                    if(matrix[i][j][k].isExists())
                    {
                        float length = getLength();
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
                                    QVector3D x = mix(base[0], base[1], (float)(i + ii)  / (float)getXsize());
                                    QVector3D y = mix(base[2], base[3], (float)(j + jj) / (float)getYsize());
                                    QVector3D z = mix(base[4], base[5], (float)(k + kk) / (float)getZsize());
                                    normal[ii + jj * 2 + kk * 4] = mix(x, y, z);
                                }

                        program->bind();
                        program->setUniformValue(u_color, matrix[i][j][k].getColor());
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

                        if(GridFlag == 2)
                        {

                            program->bind();
                            program->setUniformValue(u_color, black);
                            vao.bind();
                            glLineWidth(2);
                            glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, lineIndices);
                            vao.release();
                            program->release();
                        }


                    }


                }
            if(MoleFlag == 2)
            {
                MoleMatrix.resize(getMoleXsize());
                for(int i = 0; i < getMoleXsize(); ++i)
                {
                    MoleMatrix[i].resize(getMoleYsize());
                    for(int j = 0; j < getMoleYsize(); j++)
                        MoleMatrix[i][j].resize(getMoleZsize());
                }


                QVector3D white = QVector3D (1.0f, 1.0f, 1.0f);
                for(int i = getXsize() + 1 - Xdirection; i < getXsize() + 1 + getMoleXsize() - Xdirection; ++i)
                    for(int j = getYsize() + 1 - Ydirection; j < getYsize() + 1 + getMoleYsize() - Ydirection; ++j)
                        for(int k = getZsize() +1 - Zdirection; k < getZsize() + 1 + getMoleZsize() - Zdirection; ++k)
                        {

                                float length = getLength();
                                QVector3D vertices[8];

                                vertices[0] = QVector3D(i * length, j * length, k * length);
                                vertices[1] = QVector3D((i + 1) * length, j * length, k * length);
                                vertices[2] = QVector3D(i * length, (j + 1) * length, k * length);
                                vertices[3] = QVector3D((i + 1) * length, (j + 1) * length, k * length);
                                vertices[4] = QVector3D(i * length, j * length, (k + 1) * length);
                                vertices[5] = QVector3D((i + 1) * length, j * length, (k + 1) * length);
                                vertices[6] = QVector3D(i * length, (j + 1) * length, (k + 1) * length);
                                vertices[7] = QVector3D((i + 1) * length, (j + 1) * length, (k + 1) * length);

                                program->bind();
                                program->setUniformValue(u_color, black);
                                bufferForVertices.bind();
                                bufferForVertices.allocate(vertices, sizeof(vertices));


                                vao.bind();
                                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
                                vao.release();
                                bufferForVertices.release();
                                program->release();

                                program->bind();
                                program->setUniformValue(u_color, white);
                                vao.bind();
                                glLineWidth(2);
                                glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, lineIndices);
                                vao.release();
                                program->release();


                        }
            }



    }
}


void Drawer:: paintGrid(int state)
{
    GridFlag = state;
    scene = Scene();
    Drawer::update();
}

void Drawer::DeleteLayerX(int x)
{

    int  y,z;
    y = getYsize();
    z = getZsize();
    sizeX = x;
    setExist(x,y,z);
    scene = Scene();
    QWidget::update();

}

void Drawer::DeleteLayerY(int y)
{
    int  x,z;

    x = getXsize();
    z = getZsize();
    sizeY = y;
    setExist(x,y,z);
    scene = Scene();
    QWidget::update();
}

void Drawer::DeleteLayerZ(int z)
{

    int  y,x;

    y = getYsize();
    x = getXsize();
    sizeZ = z;
    setExist(x,y,z);
    scene = Scene();
    QWidget::update();
}

void Drawer::CameraCenter(int state)
{
    camera.setCameraLockFlag(state);
    scene = Scene();
    QWidget::update();
}

void Drawer::DrawMole(int state)
{
    MoleFlag = state;
    scene = Scene();
    QWidget::update();
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
    if(event->key() == Qt::Key_Up)
        MoleMoveForward(1);
    if(event->key() == Qt::Key_Down)
        MoleMoveForward(-1);
    if(event->key() == Qt::Key_Left)
        MoleMoveRight(1);
    if(event->key() == Qt::Key_Right)
        MoleMoveRight(-1);
    if(event->key() == Qt::Key_Control)
        MoleMoveUp(-1);
    if(event->key() == Qt::Key_Shift)
        MoleMoveUp(1);
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
        if(camera.getCameraLockFlag() == 0)
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
        }

        else
        {
            camera.rotateX((rotatingSpeed/4) * (GLfloat)(pe->x() - ptrMousePosition.x()) / width());
            camera.rotateY((rotatingSpeed/4) * (GLfloat)(pe->y() - ptrMousePosition.y()) / height());
            ptrMousePosition = pe->pos();

            program->bind();
            program->setUniformValue(u_worldToCamera, camera.toMatrix());
            program->release();
        }
    }
    QWidget::update();
}

void Drawer::mouseReleaseEvent(QMouseEvent*)
{
    pressed = false;
    QWidget::update();
}






void Drawer::update()
{
    QWidget::update();
}
