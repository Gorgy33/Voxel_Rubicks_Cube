#ifndef CAMERA_H
#define CAMERA_H
#include <QMAtrix4x4>



class Camera
{
public:
    Camera();
    void rotateX(float angle);
    void rotateY(float angle);
    void zoomIn();
    void zoomOut();

    QMatrix4x4 toMatrix();

private:
    bool dirty;
    float xAngle;
    float yAngle;
    float radius;

    QVector3D position;

    QMatrix4x4 world;
};

#endif // CAMERA_H
