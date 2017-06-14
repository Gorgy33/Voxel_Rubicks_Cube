#include "camera.h"

const QVector3D Camera::LOCAL_FORWARD(0.0f, 0.0f, -1.0f);
const QVector3D Camera::LOCAL_UP(0.0f, 1.0f, 0.0f);
const QVector3D Camera::LOCAL_RIGHT(1.0f, 0.0f, 0.0f);

Camera::Camera()
{
    dirty = true;
    translation = QVector3D(1.5f, 1.5f, 10.0f);
    setRotation(0.0f, LOCAL_UP);

}

void Camera::setRotation(float xRot, const QVector3D axis)
{
    dirty = true;
    this->rotation = QQuaternion::fromAxisAndAngle(axis, xRot)
            * this->rotation;
}

void Camera::translateBy(float speed, const QVector3D axis)
{
    dirty = true;
    translation += speed * axis;
}

QMatrix4x4 Camera::toMatrix()
{
    if(dirty)
    {
        world.setToIdentity();
        world.rotate(rotation.conjugated());
        world.translate(-translation);
//        if(drawer.CameraFlag == 2)
//            world.lookAt(QVector3D(0.0f,0.5f,0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
        dirty = false;
    }
    return world;
}

QVector3D Camera::forward() const
{
    return rotation.rotatedVector(LOCAL_FORWARD);
}

QVector3D Camera::up() const
{
    return rotation.rotatedVector(LOCAL_UP);
}

QVector3D Camera::right() const
{
    return rotation.rotatedVector(LOCAL_RIGHT);
}





