#ifndef DRAWER_H
#define DRAWER_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QQuaternion>

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

private:
    Scene scene;
    QOpenGLShaderProgram *program;
    QOpenGLBuffer bufferForVertices;
    QOpenGLBuffer bufferForIndices;
    QOpenGLVertexArrayObject vao;

    Camera camera;
    QMatrix4x4 cameraToView;
    QMatrix4x4 modelToWorld;

    GLuint u_modelToWorld;
    GLuint u_worldToCamera;
    GLuint u_cameraToView;

    GLuint u_color;

    float cameraSpeed       = 1.0f;
    float rotatingSpeed     = 100.0f;

    bool pressed;
    QPoint ptrMousePosition;

protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
protected slots:
    void update();
};

#endif // DRAWER_H
