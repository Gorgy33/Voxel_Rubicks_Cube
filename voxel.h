#ifndef VOXEL_H
#define VOXEL_H

#include <QMainWindow>

namespace Ui {
class Voxel;
}

class Voxel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Voxel(QWidget *parent = 0);
    ~Voxel();

private:
    Ui::Voxel *ui;
};

#endif // VOXEL_H
