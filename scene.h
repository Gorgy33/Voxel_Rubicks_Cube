#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "voxelparameter.h"

using namespace std;

class Scene
{
public:
    Scene(float length, int NodeSizeX, int NodeSizeY, int NodeSizeZ);
    Scene();
    bool isReady()      { return ready; }

    int getXsize()      { return sizeX; }
    int getYsize()      { return sizeY; }
    int getZsize()      { return sizeZ; }

    float getLength()   { return sideLength; }

    VoxelParam getElem(int i, int j, int k);
private:
    int sizeX;
    int sizeY;
    int sizeZ;
    vector< vector < vector < VoxelParam > > > matrix;
    float sideLength;
    bool ready = false;
};

#endif // SCENE_H
