#include "drawer.h"
#include <QMouseEvent>
#include <fstream>



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

void Drawer::setDrawStatus(int x, int y, int z) //FRLBTH
{
    //x - ширина, y - высота, z - глубина
    if (x == 0)
    {
        if(y == 0)
        {
            if (z == 0)
                matrix[x][y][z].setStatus("LBH");
            else if (z == NodeSizeZ-1)
                matrix[x][y][z].setStatus("FLB");
            else // x == 0 && y == 0 && 0<z<NodeSizeZ
                matrix[x][y][z].setStatus("LB");
        }
        else if (y == NodeSizeY-1)
        {
            if (z == 0)
                matrix[x][y][z].setStatus("LTH");
            else if (z == NodeSizeZ-1)
                matrix[x][y][z].setStatus("FLT");
            else // x == 0 && y == NodeSizeY && 0<z<NodeSizeZ
                matrix[x][y][z].setStatus("LT");

        }
        else if(z == 0)
            matrix[x][y][z].setStatus("LH");
        else if(z == NodeSizeZ-1)
            matrix[x][y][z].setStatus("FL");
        else // x == 0 && 0<y<NodeSizeY && 0<z<NodeSizeZ
            matrix[x][y][z].setStatus("L");
    }
    else if(x == NodeSizeX-1)
    {
        if(y == 0)
        {
            if (z == 0)
                matrix[x][y][z].setStatus("RBH");
            else if (z == NodeSizeZ-1)
                matrix[x][y][z].setStatus("FRB");
            else
                matrix[x][y][z].setStatus("RB");
        }
        else if (y == NodeSizeY-1)
        {
            if (z == 0)
                matrix[x][y][z].setStatus("RTH");
            else if (z == NodeSizeZ-1)
                matrix[x][y][z].setStatus("FRT");
            else
                matrix[x][y][z].setStatus("RT");
        }
        else if(z == 0)
            matrix[x][y][z].setStatus("RH");
        else if(z == NodeSizeZ-1)
            matrix[x][y][z].setStatus("FR");
        else
            matrix[x][y][z].setStatus("R");
    }
    else if(y == 0)  // 0<x<NodeSizeX
    {
        if(z == 0)
            matrix[x][y][z].setStatus("BH");
        else if(z == NodeSizeZ-1)
            matrix[x][y][z].setStatus("FB");
        else
            matrix[x][y][z].setStatus("B");
    }
    else if(y == NodeSizeY-1)
    {
        if(z == 0)
            matrix[x][y][z].setStatus("TH");
        else if(z == NodeSizeZ-1)
            matrix[x][y][z].setStatus("FT");
        else
            matrix[x][y][z].setStatus("T");
    }
    else if(z == 0) // 0<x<NodeSizeX && 0<y<NodeSizeY
        matrix[x][y][z].setStatus("H");
    else if(z == NodeSizeZ-1)
        matrix[x][y][z].setStatus("F");

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
                //                r = rand()%256;
                //                r = r/255;
                //                g = rand()%256;
                //                g = g/255;
                //                b = rand()%256;
                //                b = b/255;
                r = 0.0f;
                g = 128.0f;
                b = 0.0f;

                color = QVector3D(r, g, b);

                matrix[i][j][k].setColor(color);
            }

}

void Drawer:: setExist(int x, int y, int z)
{
    if (!BoxFlag)
    {
        for(int i = 0; i < x; ++i)
            for(int j = 0; j < y; ++j)
                for(int k = 0; k < z; ++k)
                {

                    if(((i == 0) || (i == (x -1)) || (j == 0) ||  (j == (y -1)) || (k == 0) ||  (k == (z -1))) && !matrix[i][j][k].isDel())
                        //matrix[i][j][k].setExists(true);
                        setDrawStatus(i,j,k);
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
}

char Drawer::CheckDirection()
{
    int dx = (int)abs(points[1].x() - points[0].x());
    int dy = (int)abs(points[1].y() - points[0].y());
    int dz = (int)abs(points[1].z() - points[0].z());
    if(dx < dy)
        if(dx < dz)
            return 'x';
        else
            return 'z';
    else
        if(dy < dz)
            return 'y';
        else
            return 'z';
}

/*void Drawer::VoxelSplain()
{
    fstream out("log.txt", fstream::app);
    char dir = CheckDirection();
    out<<dir<<"\t";
    switch(dir)
    {
    case 'x' : {
        int x = getYsize()/(int)(abs(points[1].x() - points[0].x()));
        out<<"x="<<x<<endl;
        if(points[0].x() > points[1].x())
            for(int k = points[0].x(); k > points[1].x(); --k)
                for(int i = 0 + x*((int)points[0].x() - k); i< getXsize(); ++i)
                    for(int j = 0; j < getZsize(); ++j)
                        deleteVoxel(i,k, j);
        else
            for(int k = points[1].x(); k > points[0].x(); --k)
                for(int i = 0 + x*((int)points[1].x() - k); i< getXsize(); ++i)
                    for(int j = 0; j < getZsize(); ++j)
                        deleteVoxel(i,k, j);


        break;};
    case 'y' : {
        int y = getXsize()/(int)(abs(points[1].y() - points[0].y()));
        out<<"y="<<y<<endl;
        if(points[0].y() > points[1].y())
            for(int k = points[0].y(); k > points[1].y(); k--)
                for(int i = 0 + y*((int)points[0].y() - k); i< getXsize(); ++i)
                    for(int j = 0; j < getZsize(); ++j)
                        deleteVoxel(i,k, j);
        else
            for(int k = points[1].y(); k > points[0].y(); --k)
                for(int i = 0 + y*((int)points[1].y() - k); i< getXsize(); ++i)
                    for(int j = 0; j < getZsize(); ++j)
                        deleteVoxel(i,k, j);

        break;}
    case 'z' : {
        int z = getXsize()/(int)(abs(points[1].z() - points[0].z()));
        out<<"z="<<z<<endl;
        if(points[0].z() > points[1].z())
            for(int k = points[0].z(); k > points[1].z(); --k)
                for(int i = 0 + z*((int)points[0].z() - k); i< getXsize(); ++i)
                    for(int j = 0; j < getZsize(); ++j)
                        deleteVoxel(i,k, j);
        else
            for(int k = points[1].z(); k > points[0].z(); --k)
                for(int i = 0 + z*((int)points[1].z() - k); i< getXsize(); ++i)
                    for(int j = 0; j < getZsize(); ++j)
                        deleteVoxel(i,k, j);


        break;}
    }
}
*/


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
    LengthX=1.0f;
    LengthY=1.0f;
    LengthZ=1.0f;
    Step=0.1f;



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
    //setDrawStatus(NodeSizeX, NodeSizeY, NodeSizeZ);
    setExist(NodeSizeX, NodeSizeY, NodeSizeZ);

    scene = Scene();

}



void Drawer::initializeGL()
{
    QVector3D green = QVector3D(0.0f, 1.0f, 0.0f);
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
    program->setUniformValue(u_color, green);


    vao.create();
    vao.bind();

    bufferForVertices = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    bufferForVertices.create();
    bufferForVertices.bind();
    bufferForVertices.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 12, 0);

    bufferForNormals = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    bufferForNormals.create();
    bufferForNormals.bind();
    bufferForNormals.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    program->enableAttributeArray(1);
    program->setAttributeBuffer(1, GL_FLOAT, 0, 12, 0);

    vao.release();
    bufferForVertices.release();
    bufferForNormals.release();
    program->release();
}

void Drawer::resizeGL(int width, int height)
{
    cameraToView.setToIdentity();
    cameraToView.perspective(45.0f, width / float(height), 0.0f, 10e12f);
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

        QVector <QVector3D> normals, vert;
        QVector <int> indexes, indexes_size;
        int size = 0;
        float length = getLength();
        for(int i = 0; i < getXsize(); i++)
            for(int j = 0; j < getYsize(); j++)
                for(int k = 0; k < getZsize(); k++)
                {


                    if(matrix[i][j][k].isExists() && !matrix[i][j][k].isDel())
                    {
                        //                        data.i = i;
                        //                        data.j = j;
                        //                        data.k = k;
                        size++;
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
                        for(int a = 0; a < 8; a++)
                            normals.push_back(normal[a]);

                        //                        if(PolygonalGridFlag == 0)
                        //                        {
                        QVector3D vertices[8];

                        vertices[0] = QVector3D(i * length, j * length, k * length);
                        vertices[1] = QVector3D((i + 1) * length, j * length, k * length);
                        vertices[2] = QVector3D(i * length, (j + 1) * length, k * length);
                        vertices[3] = QVector3D((i + 1) * length, (j + 1) * length, k * length);
                        vertices[4] = QVector3D(i * length, j * length, (k + 1) * length);
                        vertices[5] = QVector3D((i + 1) * length, j * length, (k + 1) * length);
                        vertices[6] = QVector3D(i * length, (j + 1) * length, (k + 1) * length);
                        vertices[7] = QVector3D((i + 1) * length, (j + 1) * length, (k + 1) * length);

                        for(int a = 0; a < 8; a++)
                            vert.push_back(vertices[a]);

                        std::string status = matrix[i][j][k].getStatus();

                        const unsigned int indicesSize = 4*status.length();
                        int* indices = new int[indicesSize];
                        int c = 0;
                        for(unsigned int b = 0; b < status.length(); b++)
                        {
                            char s = status[b];
                            switch(s)
                            {
                            case 'F':{
                                indices[0 + 4 * c] = 4;
                                indices[1 + 4 * c] = 5;
                                indices[2 + 4 * c] = 7;
                                indices[3 + 4 * c] = 6;
                                c++;
                                break;
                            }
                            case 'R':{
                                indices[0 + 4 * c] = 1;
                                indices[1 + 4 * c] = 3;
                                indices[2 + 4 * c] = 7;
                                indices[3 + 4 * c] = 5;
                                c++;
                                break;
                            }
                            case 'L':{
                                indices[0 + 4 * c] = 0;
                                indices[1 + 4 * c] = 2;
                                indices[2 + 4 * c] = 6;
                                indices[3 + 4 * c] = 4;
                                c++;
                                break;
                            }
                            case 'B':{
                                indices[0 + 4 * c] = 0;
                                indices[1 + 4 * c] = 1;
                                indices[2 + 4 * c] = 5;
                                indices[3 + 4 * c] = 4;
                                c++;
                                break;
                            }
                            case 'T':{
                                indices[0 + 4 * c] = 2;
                                indices[1 + 4 * c] = 3;
                                indices[2 + 4 * c] = 7;
                                indices[3 + 4 * c] = 6;
                                c++;
                                break;
                            }
                            case 'H':{
                                indices[0 + 4 * c] = 0;
                                indices[1 + 4 * c] = 1;
                                indices[2 + 4 * c] = 3;
                                indices[3 + 4 * c] = 2;
                                c++;
                                break;
                            }
                            }
                        }
                        for(int ii = 0; ii < indicesSize; ii++)
                            indexes.push_back(indices[ii]);
                        indexes_size.push_back(indicesSize);
                        //                            if(GridFlag == 2)
                        //                            {

                        //                                program->bind();
                        //                                program->setUniformValue(u_color, black);
                        //                                vao.bind();
                        //                                glLineWidth(2);
                        //                                glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, lineIndices);
                        //                                vao.release();
                        //                                program->release();
                        //                            }

                        //                        }
                        //                        else
                        //                        {
                        //                            int count = 0;
                        //                            VoxelCenterPoint[count] = QVector3D((((i * length) + (i+1)*length)/2.0f), (((j * length) + (j+1)*length)/2.0f), (((k * length) + (k+1)*length)/2.0f));
                        //                            count++;
                        //                            for(int ii = -1; ii < 2; ii++)
                        //                                for(int jj = -1; jj < 2; jj++)
                        //                                    for(int kk = -1; kk < 2; kk++)
                        //                                    {
                        //                                        if(((i+ii) < 0) || ((j+jj) < 0) || ((k+kk) < 0))
                        //                                            continue;
                        //                                        if(((i+ii+1) > getXsize()) || ((j+jj+1) >getYsize()) || ((k+kk+1) >getZsize()))
                        //                                            continue;
                        //                                        if(matrix[i+ii][j+jj][k+kk].isExists() && !matrix[i+ii][j+jj][k+kk].isDel())
                        //                                        {
                        //                                            VoxelCenterPoint[count] = QVector3D(((((i+ii) * length) + ((i+ii+1)*length))/2.0f), ((((j+jj) * length) + ((j+jj+1)*length))/2.0f), ((((k+kk) * length) + ((k+kk+1)*length))/2.0f));
                        //                                            count++;
                        //                                        }
                        //                                        if(count == 3)
                        //                                        {
                        //                                            program->bind();
                        //                                            program->setUniformValue(u_color, green);
                        //                                            bufferForVertices.bind();
                        //                                            bufferForVertices.allocate(VoxelCenterPoint, sizeof(VoxelCenterPoint));
                        //                                            bufferForNormals.bind();
                        //                                            bufferForNormals.allocate(normal, sizeof(normal));

                        //                                            vao.bind();
                        //                                            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, quadIndices);
                        //                                            vao.release();
                        //                                            bufferForVertices.release();
                        //                                            bufferForNormals.release();
                        //                                            program->release();
                        //                                            if(GridFlag == 2)
                        //                                            {
                        //                                                program->bind();
                        //                                                program->setUniformValue(u_color, black);
                        //                                                bufferForVertices.bind();
                        //                                                bufferForVertices.allocate(VoxelCenterPoint, sizeof(VoxelCenterPoint));
                        //                                                vao.bind();
                        //                                                glLineWidth(2);
                        //                                                glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, trianglelineIndices);
                        //                                                vao.release();
                        //                                                bufferForVertices.release();
                        //                                                program->release();
                        //                                            }
                        //                                            if(kk == 0)
                        //                                            {
                        //                                                VoxelCenterPoint[1] = VoxelCenterPoint[2];
                        //                                                count = 2;
                        //                                            }
                        //                                            else
                        //                                                count = 1;

                        //                                        }
                        //                                    }

                        //                        }

                        //                    }

                    }

                    /* if(MoleFlag == 2)
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
                        if(delflag)
                            for(int ii = 0; ii < getXsize(); ii++)
                                for(int jj = 0; jj < getYsize(); jj++)
                                    for(int kk = 0; kk < getZsize(); kk++)
                                        if((i == ii) && (j == jj) & (k == kk))
                                            deleteVoxel(i,j,k);
                    }
        }*/
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

//        fstream tmp("C:\\Users\\Egor0\\Downloads\\Voxel_Rubicks_Cube-20181203T050944Z-001\\Voxel_Rubicks_Cube\\tmp.txt", fstream::app);
//        tmp << sizeof(normals) << " " <<  << std::endl;
        normals.resize(size);
        vert.resize(size);
        indexes.resize(size);
        indexes_size.resize(size);
//        tmp.close();
//        bufferForVertices.bind();
//        bufferForVertices.allocate(&vert, sizeof(float)*vert.size());
//        bufferForNormals.bind();
//        bufferForNormals.allocate(&normals, sizeof(float)*normals.size());
//        bufferForVertices.release();
//        bufferForNormals.release();
//        for(int i = 0; i < getXsize(); i++)
//            for(int j = 0; j < getYsize(); j++)
        //                for(int k = 0; k < getZsize(); k++)
        //                {

        program->bind();
        //program->setUniformValue(u_color, matrix[i][j][k].getColor());

        bufferForVertices.bind();
        bufferForVertices.allocate(&vert, sizeof(float)*vert.size());
        bufferForNormals.bind();
        bufferForNormals.allocate(&normals, sizeof(float)*normals.size());
        //                    bufferForVertices.bind();
        //                    bufferForNormals.bind();
        vao.bind();
        glDrawElements(GL_QUADS, 0, GL_UNSIGNED_INT, 0); // почитать про примитивы
        vao.release();
        //                    bufferForVertices.release();
        //                    bufferForNormals.release();
        program->release();
        //                }
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
        if(event->key() == Qt::Key_5)
        {
            delflag++;
            delflag%=2;
            scene = Scene();
            QWidget::update();
        }
        /*if(event->key() == Qt::Key_7)
        {
            points[pointcount] = QVector3D((int)(getXsize() - Xdirection - 1), (int)(getYsize() - Ydirection - 1), (int)(getZsize() - Zdirection - 1));
            pointcount++;
            if(pointcount == 2)
            {
                VoxelSplain();
                pointcount = 0;
            }
        }*/
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
