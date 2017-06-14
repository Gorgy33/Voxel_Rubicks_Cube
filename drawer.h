#pragma once
#ifndef DRAWER_H
#define DRAWER_H


#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QLCDNumber>
#include <QSlider>
#include <QLayout>
#include <QCheckBox>
#include <QWidget>
#include <QLayout>
#include <conio.h>
#include <QPushButton>
#include <vector>

#include "scene.h"
#include "voxelparameter.h"
#include "camera.h"



class QOpenGLShaderProgram;

class Drawer : public QOpenGLWidget,
               protected QOpenGLFunctions
{
    Q_OBJECT
public:
    ~Drawer();
    Drawer(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    int GridFlag = 0;
    int MoleFlag = 0;

    int getXsize()      { return sizeX; }
    int getYsize()      { return sizeY; }
    int getZsize()      { return sizeZ; }

    float getLength()   { return sideLength; }
    void setCollor(int x, int y, int z);
    void setExist(int x, int y, int z);

    int getMoleXsize()      { return moleXsize; }
    int getMoleYsize()      { return moleYsize; }
    int getMoleZsize()      { return moleZsize; }



    void MoleMoveForward(int direction);
    void MoleMoveRight(int direction);
    void MoleMoveUp(int direction);

    int Xdirection = 0, Ydirection = 0, Zdirection = 0;

\
public slots:
    void paintGrid(int state);
    void DeleteLayerX(int x);
    void DeleteLayerY(int y);
    void DeleteLayerZ(int z);
    void CameraCenter(int state);
    void DrawMole(int state);

private:
    Scene scene;
    QOpenGLShaderProgram *program;
    QOpenGLBuffer bufferForVertices;
    QOpenGLBuffer bufferForNormals;

    QOpenGLVertexArrayObject vao;

    Camera camera;
    QMatrix4x4 cameraToView;
    QMatrix4x4 modelToWorld;

    GLuint u_modelToWorld;
    GLuint u_worldToCamera;
    GLuint u_cameraToView;

    GLuint u_color;

    float cameraSpeed       = 1.0f;
    float rotatingSpeed     = 40.0f;

    bool pressed;
    QPoint ptrMousePosition;

    vector< vector < vector < VoxelParam > > > matrix;

    vector< vector < vector < VoxelParam > > > MoleMatrix;
    int sizeX;
    int sizeY;
    int sizeZ;
    float sideLength;

    int moleXsize = 2;
    int moleYsize = 1;
    int moleZsize = 2;



protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
protected slots:
    void update();
};

#endif // DRAWER_H
