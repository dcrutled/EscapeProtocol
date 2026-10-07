#ifndef POINT_H
#define POINT_H

#include <string>
#include <limits>


struct Point { //point object for planets, stars, player, npc, etc
    std::string name;
    int position;
    int ring;
    int radius = 0;
    float theta = 0.0;
    float xcoord;
    float ycoord;
};


struct ShortestPath {
    double distance = std::numeric_limits<double>::infinity();
    int parent = -1;
};

#endif