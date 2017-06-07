#include "scene.h"

int layernumber (int i, int j, int k, int Nodesize, int a, int b, int layer)
{

    if((i == a) || (i == (Nodesize -b)) || (j == a) ||  (j == (Nodesize -b)) || (k == a) ||  (k == (Nodesize -b)))
    {
        return layer;
    }
    else
    {
        a++;
        b++;
        layer++;
        return layernumber(i,j,k,Nodesize,a,b, layer);
    }
}



Scene::Scene(float length, int NodesizeX, int NodesizeY, int NodesizeZ)
{
    matrix.resize(NodesizeX);
    for(int i = 0; i < NodesizeX; ++i)
    {
        matrix[i].resize(NodesizeY);
        for(int j = 0; j < NodesizeY; j++)
            matrix[i][j].resize(NodesizeZ);
    }
    ready = true;
    sideLength = length;
    sizeX = NodesizeX;
    sizeY = NodesizeY;
    sizeZ = NodesizeZ;

    float r,g,b;
    double value;
    double red, blue, yellow, green, minblue, rad;
    minblue = 1/((NodesizeX/2.0)*(NodesizeX/2.0));
    if(NodesizeX/2.0 == 0)
        red = length;
    else
        red = length/((NodesizeX%2)*(NodesizeX%2));
//    red = 1;
//    blue = 0.25;
//    green = 0.5;
//    yellow = 0.75;
    blue = minblue + (red - minblue) / 4; // ~0.287 for 9x9x9 grid
    yellow = red - (red - minblue) / 4; // ~0.7623 for 9x9x9 grid
    green = minblue + (red - minblue) / 2; // ~0.525 for 9x9x9 grid

    int layernum;

    for(int i = 0; i < NodesizeX; ++i)
        for(int j = 0; j < NodesizeY; ++j)
            for(int k = 0; k < NodesizeZ; ++k)
            {

//                if((i == 0) || (i == (NodesizeX -1)) || (j == 0) ||  (j == (NodesizeY -1)) || (k == 0) ||  (k == (NodesizeZ -1)))
//                    matrix[i][j][k].setExists(true);
//                else
//                    matrix[i][j][k].setExists(false);
                // Это убирает внешний воксель
//                if((i == 25 && j == 25) /*|| (i == 4 && j == 6) || (i == 4 && j == 4) || (i == 5 && j == 4) || (i == 4 && j == 5) || (i == 5 && j == 5) || (i == 6 && j == 5) || (i == 5 && j == 6) || (i == 6 && j == 6)*/)
//                    matrix[i][j][k].setExists (true);
//                else
//                    matrix[i][j][k].setExists(false);
//                if((i == 3 && j == 3) || (i == 2 && j == 2))
//                    matrix[i][j][k].setExists(false);
//                if(k >= 25)
//                    matrix[i][j][k].setExists(true);
//                else
//                    matrix[i][j][k].setExists(false);

                if(matrix[i][j][k].isExists())
                {
                    QVector3D color;
                    r = rand()%256;
                    r = r/255;
                    g = rand()%256;
                    g = g/255;
                    b = rand()%256;
                    b = b/255;
//Курсач
//                    layernum = layernumber(i,j,k,NodesizeX, 0, 1, 0);


//                    rad = (NodesizeX/2.0) - length*layernum;

//                    value = length / (rad*rad);

//                    int collorDeflection;
//                    if (value <= (minblue))
//                    {
//                        r = 0;	g = 0;	b = 255;
//                    }
//                    else
//                        if (value <= blue)
//                        {
//                            collorDeflection = 255 * (abs(blue - minblue) - abs(value - minblue)) / abs(blue - minblue);
//                            r = 0;	g = collorDeflection; b = 255;
//                        }
//                        else
//                            if (value <= green)
//                            {
//                                collorDeflection = 255 * (abs(green - blue) - abs(value - blue)) / abs(green - blue);
//                                r = 0; g = 255 - collorDeflection; b = 0;
//                            }
//                            else
//                                if (value <= yellow)
//                                {
//                                    collorDeflection = 255 * (abs(yellow - green) - abs(value - green)) / abs(yellow - green);
//                                    r = 255 - collorDeflection; g = 255; b = 0;
//                                }
//                                else
//                                {
//                                    collorDeflection = 255 * (abs(red - yellow) - abs(value - yellow)) / abs(red - yellow);
//                                    r = 255 - collorDeflection; g = 0; b = 0;
//                                }


                    color = QVector3D(r, g, b);

                    matrix[i][j][k].setColor(color);
                }

            }
}

Scene::Scene()
{

}

VoxelParam Scene::getElem(int i, int j, int k)
{
    return matrix[i][j][k];
}
