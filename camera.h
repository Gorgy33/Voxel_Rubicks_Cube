#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <QMAtrix4x4>
#include <math.h>



class Camera
{
public:
    Camera();
    void setRotation(float xRot, const QVector3D axis);
    void translateBy(float speed, const QVector3D axis);

    QVector3D forward() const;
    QVector3D up() const;
    QVector3D right() const;



    QMatrix4x4 toMatrix();

private:
    bool dirty;
    QVector3D translation;
    QQuaternion rotation;

    const static QVector3D LOCAL_FORWARD;
    const static QVector3D LOCAL_UP;
    const static QVector3D LOCAL_RIGHT;

    QMatrix4x4 world;
};

#endif // CAMERA_H
