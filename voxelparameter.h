#ifndef VOXELPARAMETER_H
#define VOXELPARAMETER_H
#include <QVector3D>

class VoxelParam
{
public:
    VoxelParam() {
        color = QVector3D(0.3f, 0.3f, 0.3f);
        exists = true;
        del = false;
    }

    QVector3D getColor()  { return color; }
    bool isExists()       { return exists; }
    bool isDel()          { return del;}
    void setColor(QVector3D color) { this->color = color; }
    void setExists(bool exists)    { this->exists = exists; }
    void setDel(bool del)          { this->del = del;}
private:
    QVector3D color;
    bool exists;
    bool del;
};
#endif // VOXELPARAMETER_H
