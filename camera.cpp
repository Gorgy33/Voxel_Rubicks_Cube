#include "camera.h"

Camera::Camera()
{
    dirty = true;
    xAngle = M_PI / 4.0;
    yAngle = M_PI / 6.0;
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
    if(fabs(yAngle + angle) < M_PI / 2.0)
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
