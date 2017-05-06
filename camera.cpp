#include "camera.h"

Camera::Camera()
{
    dirty = true;
    xAngle = 3.14f / 4.0f;
    yAngle = 3.14f / 6.0f;
    radius = 6.0f;
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

void Camera::zoomIn()
{
    dirty = true;
    if(radius < 10.0f)
        radius *= 1.1f;
}

void Camera::zoomOut()
{
    dirty = true;
    if(radius > 1.0f / 0.9f)
        radius *= 0.9f;
}

QMatrix4x4 Camera::toMatrix()
{
    if(dirty)
    {
        world.setToIdentity();
        position = QVector3D(radius * sin(xAngle) * cos(yAngle) + 1.5f,
                             radius * sin(yAngle) + 1.5f,
                             radius * (cos(xAngle) * cos(yAngle)) + 1.5f);
        world.lookAt(position, QVector3D(1.5f, 1.5f, 1.5f), QVector3D(0.0f, 1.0f, 0.0f));
        dirty = false;
    }
    return world;
}
