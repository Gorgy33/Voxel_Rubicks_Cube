#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "voxelparameter.h"

using namespace std;

class Scene
{
public:
    Scene();
    bool isReady()      { return ready; }
private:
    bool ready = false;
};

#endif // SCENE_H
