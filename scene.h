#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "voxelparameter.h"

using namespace std;

class Scene
{
public:
    Scene(float length, int size);
    Scene();
    bool isReady()      { return ready; }

    int getXsize()      { return sizeX; }
    int getYsize()      { return sizeY; }
    int getZsize()      { return sizeZ; }

    float getLength()   { return sideLength; }

    VoxelParam getElem(int i, int j, int k);
private:
    vector< vector < vector < VoxelParam > > > matrix;
    float sideLength;
    bool ready = false;

    int sizeX;
    int sizeY;
    int sizeZ;
};

#endif // SCENE_H
