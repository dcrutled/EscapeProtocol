#ifndef POINT_H
#define POINT_H

#include <string>


struct Point {
    std::string name;
    int position;
    int ring;
    int radius = 0;
    float theta = 0.0;
    float xcoord;
    float ycoord;
};


#endif