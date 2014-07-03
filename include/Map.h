#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
using namespace std;

class Map
{
public:
    static Map MapControl;

    Map();

    void loadMap(string filename);
    void saveMap(string filename);

    void createMap(int width);

    string map_name = "output.map";

    vector<int> fases;
};

#endif // MAP_H
