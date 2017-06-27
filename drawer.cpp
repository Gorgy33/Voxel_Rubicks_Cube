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

int quadIndices[3] =
{
    0, 1, 2
};
int trianglelineIndices[6] =
{
  0, 1, 0, 2,
  1, 2
};


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

                color = QVector3D(r, g, b);

                matrix[i][j][k].setColor(color);
            }

}

void Drawer:: setExist(int x, int y, int z)
{
    if (BoxFlag == 2)
    {
        for(int i = 0; i < x; ++i)
            for(int j = 0; j < y; ++j)
                for(int k = 0; k < z; ++k)
                {

                    if(((i == 0) || (i == (x -1)) || (j == 0) ||  (j == (y -1)) || (k == 0) ||  (k == (z -1))) && !matrix[i][j][k].isDel())
                        matrix[i][j][k].setExists(true);
                    else
                        matrix[i][j][k].setExists(false);
                }
    }
    else
    {
        for(int i = 0; i < x; ++i)
            for(int j = 0; j < y; ++j)
                for(int k = 0; k < z; ++k)
                {
                    if((i <= (x-1)) || (j <= (y-1)) || (k <= (z-1) ))
                        matrix[i][j][k].setExists(true);
                    else
                        matrix[i][j][k].setExists(false);
                }
    }

    if(test1 == 1)
    {
        for(int i = 0; i < x; ++i)
            for(int j = 0; j < y; ++j)
                for(int k = 0; k < z; ++k)
                {
                   matrix[i][j][k].setExists(false);
                }
        int i=0;
        while(i<x)
        {
            for(int j = 0; j < i; ++j)
                for(int k = 0; k < i; ++k)
                {
                    matrix[i][j][k].setExists(true);
                }
            i++;
        }
    }

}




void Drawer::MoleMoveForward(int direction)
{
    Zdirection  = Zdirection + direction;
    scene = Scene();
    QWidget::update();
}

void Drawer::MoleMoveLeft(int direction)
{
    Xdirection  = Xdirection + direction;
    scene = Scene();
    QWidget::update();
}

void Drawer::MoleMoveDown(int direction)
{
    Ydirection  = Ydirection + direction;
    scene = Scene();
    QWidget::update();
}

void Drawer::deleteVoxel(int i, int j, int k)
{
    matrix[i][j][k].setDel(true);
    if(BoxFlag == 2)
    {
        if(((i+1) < getXsize()) && ((j+1) < getYsize()) && ((k+1) < getZsize()) && ((i-1) > 0) && ((j-1) > 0) && ((k-1) > 0))
        {
            matrix[i+1][j][k].setExists(true);
            matrix[i+1][j+1][k].setExists(true);
            matrix[i+1][j][k+1].setExists(true);
            matrix[i+1][j+1][k+1].setExists(true);
            matrix[i][j+1][k].setExists(true);
            matrix[i][j+1][k+1].setExists(true);
            matrix[i][j][k+1].setExists(true);
            matrix[i-1][j][k].setExists(true);
            matrix[i-1][j-1][k].setExists(true);
            matrix[i-1][j][k-1].setExists(true);
            matrix[i-1][j-1][k-1].setExists(true);
            matrix[i][j-1][k].setExists(true);
            matrix[i][j-1][k-1].setExists(true);
            matrix[i][j][k-1].setExists(true);
            matrix[i+1][j][k-1].setExists(true);
            matrix[i-1][j][k+1].setExists(true);

        }
        else
            if(((i-1) > 0) && ((j-1) > 0) && ((k-1) > 0))
            {
                matrix[i-1][j][k].setExists(true);
                matrix[i-1][j-1][k].setExists(true);
                matrix[i-1][j][k-1].setExists(true);
                matrix[i-1][j-1][k-1].setExists(true);
                matrix[i][j-1][k].setExists(true);
                matrix[i][j-1][k-1].setExists(true);
                matrix[i][j][k-1].setExists(true);

            }
    }
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
    LengthX=3.0f;
    LengthY=3.0f;
    LengthZ=3.0f;
    Step=0.1f;


    int NodeSizeX, NodeSizeY, NodeSizeZ;
    NodeSizeX = LengthX/Step;
    NodeSizeY = LengthY/Step;
    NodeSizeZ = LengthZ/Step;

    camera.cameraCenterX=LengthX/2.0f;
    camera.cameraCenterY=LengthY/2.0f;
    camera.cameraCenterZ=LengthZ/2.0f;

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
    QCheckBox *ShowBox = new QCheckBox(tr("Show only outer layer"), parent);
    ShowBox->setGeometry(900, 400, 125, 50);
    QCheckBox *PolygonalGrid = new QCheckBox(tr("Switch to Polygonal Grid"), parent);
    PolygonalGrid->setGeometry(900, 300, 135, 50);


    QPushButton *Help = new QPushButton(tr("Help"), parent);
    Help->setGeometry(900, 550, 70, 20);

    connect(Help, SIGNAL(pressed()), this, SLOT(HelpWindow()));
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
    connect(ShowBox, SIGNAL(stateChanged(int)), this, SLOT(DrawBox(int)));
    connect(PolygonalGrid, SIGNAL(stateChanged(int)), this, SLOT(paintPolygonalGrid(int)));

    sideLength = Step;
    oldSizeX = NodeSizeX;
    oldSizeY = NodeSizeY;
    oldSizeZ = NodeSizeZ;

    setCollor(NodeSizeX, NodeSizeY, NodeSizeZ);

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
        QVector3D green = QVector3D(0.0f, 1.0f, 0.0f);
        QVector3D VoxelCenterPoint[3];

        float length = getLength();
        for(int i = 0; i < getXsize(); i++)
            for(int j = 0; j < getYsize(); j++)
                for(int k = 0; k < getZsize(); k++)
                {


                    if(matrix[i][j][k].isExists() && !matrix[i][j][k].isDel())
                    {
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
                        if(PolygonalGridFlag == 0)
                        {
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
                        else
                        {
                            int count = 0;
                            VoxelCenterPoint[count] = QVector3D((((i * length) + (i+1)*length)/2.0f), (((j * length) + (j+1)*length)/2.0f), (((k * length) + (k+1)*length)/2.0f));
                            count++;
                            for(int ii = -1; ii < 2; ii++)
                                for(int jj = -1; jj < 2; jj++)
                                    for(int kk = -1; kk < 2; kk++)
                                    {
                                        if(((i+ii) < 0) || ((j+jj) < 0) || ((k+kk) < 0))
                                            continue;
                                        if(((i+ii+1) > getXsize()) || ((j+jj+1) >getYsize()) || ((k+kk+1) >getZsize()))
                                            continue;
                                        if(matrix[i+ii][j+jj][k+kk].isExists() && !matrix[i+ii][j+jj][k+kk].isDel())
                                        {
                                                VoxelCenterPoint[count] = QVector3D(((((i+ii) * length) + ((i+ii+1)*length))/2.0f), ((((j+jj) * length) + ((j+jj+1)*length))/2.0f), ((((k+kk) * length) + ((k+kk+1)*length))/2.0f));
                                                count++;
                                        }
                                        if(count == 3)
                                        {
                                            program->bind();
                                            program->setUniformValue(u_color, green);
                                            bufferForVertices.bind();
                                            bufferForVertices.allocate(VoxelCenterPoint, sizeof(VoxelCenterPoint));
                                            bufferForNormals.bind();
                                            bufferForNormals.allocate(normal, sizeof(normal));

                                            vao.bind();
                                            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, quadIndices);
                                            vao.release();
                                            bufferForVertices.release();
                                            bufferForNormals.release();
                                            program->release();
                                            if(GridFlag == 2)
                                            {
                                                program->bind();
                                                program->setUniformValue(u_color, black);
                                                bufferForVertices.bind();
                                                bufferForVertices.allocate(VoxelCenterPoint, sizeof(VoxelCenterPoint));
                                                vao.bind();
                                                glLineWidth(2);
                                                glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, trianglelineIndices);
                                                vao.release();
                                                bufferForVertices.release();
                                                program->release();
                                            }
                                            if(kk == 0)
                                            {
                                                VoxelCenterPoint[1] = VoxelCenterPoint[2];
                                                count = 2;
                                            }
                                            else
                                                count = 1;

                                        }
                                    }

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
        for(int i = getXsize() - Xdirection; i < getXsize() + getMoleXsize() - Xdirection; ++i)
            for(int j = getYsize() - Ydirection; j < getYsize() + getMoleYsize() - Ydirection; ++j)
                for(int k = getZsize() - Zdirection; k < getZsize() + getMoleZsize() - Zdirection; ++k)
                {
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
                    program->setUniformValue(u_color, white);
                    bufferForVertices.bind();
                    bufferForVertices.allocate(vertices, sizeof(vertices));

                    vao.bind();
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
                    vao.release();
                    bufferForVertices.release();
                    program->release();

                    program->bind();
                    program->setUniformValue(u_color, black);
                    vao.bind();
                    glLineWidth(2);
                    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, lineIndices);
                    vao.release();
                    program->release();

                    for(int ii = 0; ii < getXsize(); ii++)
                        for(int jj = 0; jj < getYsize(); jj++)
                            for(int kk = 0; kk < getZsize(); kk++)
                            {
                                if((i == ii) && (j == jj) & (k == kk))
                                    deleteVoxel(i,j,k);
                            }
                }
    }
    if(contourFlag)
    {
        QVector3D contourVertices[8];
        float x,y,z;
        x = oldSizeX;
        y = oldSizeY;
        z = oldSizeZ;
        contourVertices[0] = QVector3D(0.0f,0.0f,0.0f);
        contourVertices[1] = QVector3D(0.0f,0.0f,z*length);
        contourVertices[2] = QVector3D(0.0f,y*length,0.0f);
        contourVertices[3] = QVector3D(0.0f,y*length,z*length);
        contourVertices[4] = QVector3D(x*length,0.0f,0.0f);
        contourVertices[5] = QVector3D(x*length,0.0f,z*length);
        contourVertices[6] = QVector3D(x*length,y*length,0.0f);
        contourVertices[7] = QVector3D(x*length,y*length,z*length);
        program->bind();
        program->setUniformValue(u_color, black);
        bufferForVertices.bind();
        bufferForVertices.allocate(contourVertices, sizeof(contourVertices));

        vao.bind();
        glLineWidth(2);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, lineIndices);
        vao.release();
        bufferForVertices.release();
        program->release();
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
    if(z == oldSizeZ && x == oldSizeX && y == oldSizeY)
        contourFlag = false;
    else
        contourFlag = true;
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
    if(z == oldSizeZ && x == oldSizeX && y == oldSizeY)
        contourFlag = false;
    else
        contourFlag = true;
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
    if(z == oldSizeZ && x == oldSizeX && y == oldSizeY)
        contourFlag = false;
    else
        contourFlag = true;
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

void Drawer::DrawBox(int state)
{
    BoxFlag = state;
    int x,y,z;
    x = getXsize();
    y = getYsize();
    z = getZsize();
    setExist(x,y,z);
    scene  = Scene();
    QWidget::update();
}

void Drawer::paintPolygonalGrid(int state)
{
    PolygonalGridFlag = state;
    scene = Scene();
    QWidget::update();
}

void Drawer::HelpWindow()
{
        QString text = "<b>Управление камерой</b> <br>"
                       "W - движение камеры вперед <br> S - движение камеры назад <br> "
                       "A - движение камеры влево <br> D - движение камеры вправо <br> "
                       "Q - движение камеры вниз <br> E - движение камеры вверх <br> "
                       "Для поворота камеры необходимо зажать левую клавишу мыши и сдвинуть курсор в необходимом направлении <br>"
                       "При включенной функции блокировки камеры вместо смещения камеры будет произведен поворот объекта <br>"
                       "<br>"
                       "<b>Управление объектом \"Крот\"</b> <br>"
                       "Стрелка вверх - движение объекта \"Крот\" по направлению оси oZ <br>"
                       "Стрелка вниз - движение объекта \"Крот\" против направления оси oZ <br>"
                       "Стрелка влево - движение объекта \"Крот\" по направлению оси oX <br>"
                       "Стрелка вправо - движение объекта \"Крот\" против направления оси oX <br>"
                       "NumPad Клавиша \"1\" - движение объекта \"Крот\" против направления оси oY <br>"
                       "NumPad клавиша \"4\" - движение объекта \"Крот\" по направлению оси oY <br>";

        QLabel *lbl = new QLabel(text, nullptr);
        lbl->resize(1024, 720);
        lbl->setStyleSheet("font-size: 16px");
        lbl->show();
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
    if(MoleFlag == 2)
    {
        if(event->key() == Qt::Key_Up)
            MoleMoveForward(1);
        if(event->key() == Qt::Key_Down)
            MoleMoveForward(-1);
        if(event->key() == Qt::Key_Left)
            MoleMoveLeft(1);
        if(event->key() == Qt::Key_Right)
            MoleMoveLeft(-1);
        if(event->key() == Qt::Key_1)
            MoleMoveDown(1);
        if(event->key() == Qt::Key_4)
            MoleMoveDown(-1);
    }
     if(event->key() == Qt::Key_2)
     {
        test1 = 1;
        setExist(getXsize(),getYsize(),getZsize());
        scene = Scene();
     }
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
