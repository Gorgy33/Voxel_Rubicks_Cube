#include "camera.h"

const QVector3D Camera::LOCAL_FORWARD(0.0f, 0.0f, -1.0f);
const QVector3D Camera::LOCAL_UP(0.0f, 1.0f, 0.0f);
const QVector3D Camera::LOCAL_RIGHT(1.0f, 0.0f, 0.0f);

Camera::Camera()
{
    dirty = true;
    translation = QVector3D(1.5f, 1.5f, 10.0f);
    setRotation(0.0f, LOCAL_UP);
    xAngle = 3.14f / 4.0f;
    yAngle = 3.14f / 6.0f;
    radius = 6.0f;


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
        position = QVector3D(radius * sin(xAngle) * cos(yAngle) + 1.5f,
                             radius * sin(yAngle) + 1.5f,
                             radius * (cos(xAngle) * cos(yAngle)) + 1.5f);

           world.lookAt(position, QVector3D(cameraCenterX, cameraCenterY, cameraCenterZ), QVector3D(0.0f, 1.0f, 0.0f));

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

void Camera::rotateX(float angle)
{
    dirty = true;
    xAngle += angle;
}

void Camera::rotateY(float angle)
{
    dirty = true;
    if(fabs(yAngle + angle) < 3.14f / 2.0f)
        yAngle += angle;
}





