#ifndef VOXELPARAMETER_H
#define VOXELPARAMETER_H
#include <QVector3D>
#include <string>

class VoxelParam
{
public:
    VoxelParam() {
        color = QVector3D(0.3f, 0.3f, 0.3f);
        exists = true;
        del = false;
        status = "";
    }

    QVector3D getColor()  { return color; }
    std::string getStatus() { return status; }
    bool isExists()       { return exists; }
    bool isDel()          { return del;}
    void setColor(QVector3D color) { this->color = color; }
    void setExists(bool exists)    { this->exists = exists; }
    void setDel(bool del)          { this->del = del;}
    void setStatus(std::string status) { this->status += status;}
private:
    QVector3D color;
    bool exists;
    bool del;
    std::string status;
};
#endif // VOXELPARAMETER_H
