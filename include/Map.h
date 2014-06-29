#ifndef MAP_H
#define MAP_H

#include <string>
using namespace std;

class Map
{
public:
    static Map MapControl;

    Map();

    void loadMap(string filename);
    void saveMap(string filename);

    void createMap(int width);
};

#endif // MAP_H
