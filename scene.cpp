#include "scene.h"

Scene::Scene(float length, int size)
{
    matrix.resize(size);
    for(int i = 0; i < size; ++i)
    {
        matrix[i].resize(size);
        for(int j = 0; j < size; j++)
            matrix[i][j].resize(size);
    }
    ready = true;
    sideLength = length;
    sizeX = size;
    sizeY = size;
    sizeZ = size;

    float r,g,b;

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            for(int k = 0; k < size; ++k)
            {
                QVector3D color;
                r = rand()%256;
                r = r/255;
                g = rand()%256;
                g = g/255;
                b = rand()%256;
                b = b/255;
                color = QVector3D(r, g, b);

                matrix[i][j][k].setColor(color);
//                if((i == 0) && (j == 0) && (k == 0))
//                    matrix[i][j][k].setExists(false);
            }
}

Scene::Scene()
{

}

VoxelParam Scene::getElem(int i, int j, int k)
{
    return matrix[i][j][k];
}
