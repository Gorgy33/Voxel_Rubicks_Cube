#ifndef VOXELPARAMETER_H
#define VOXELPARAMETER_H
#include <QVector3D>

class VoxelParam
{
public:
    VoxelParam() {
        color = QVector3D(0.3f, 0.3f, 0.3f);
        exists = true;
    }

    QVector3D getColor()  { return color; }
    bool isExists()       { return exists; }
    void setColor(QVector3D color) { this->color = color; }
private:
    QVector3D color;
    bool exists;
};
#endif // VOXELPARAMETER_H
