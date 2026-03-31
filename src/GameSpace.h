#ifndef GAMESPACE_H
#define GAMESPACE_H
#include <string>
#include <vector>
#include <limits>
#include "StellarBodies.h"
#include <SFML/Graphics.hpp>

using namespace std;

struct Point {
    string name;
    int position;
    int ring;
    int radius = 0;
    float theta = 0.0;
    float xcoord;
    float ycoord;
};

struct Edge {
    Point point1;
    Point point2;
    int endRing;

    int weight = 0;
    //other stuff
};


struct ShortestPath {
    double distance = numeric_limits<double>::infinity();
    int parent = -1;
};






class GameSpace {

public:

    GameSpace(int ringCount);

    void set_vertices(int vertices);
    int get_vertices() const;

    int get_ringCount() const;

    int get_Degree(int v) const;

    bool checkSymmetry() const;
    //bool checkOtherSymmetry() const;

    void createPointsAndRings(int ringCount);
    void createEdges();
    
    void makeCartesian();
    void drawMap();
    void createObstacles();
    void setEdgeWeight(int i, int k, StellarBody tempBody);
    int calculateGravity(Edge);

    void polarDistance(struct Point, struct Point);

    void draw(sf::RenderWindow& window);

    void bellmanFord();


    void testShowStuff();
   




private:
    int vertices;
    int ringCount;
    vector<Point> points;
    vector<vector<Point>> rings;
    vector<vector<int>> edges;
    vector<vector<Edge>> otherEdges;

    sf::VertexArray map;
    vector<StellarBody> stellarObjects;

    vector<ShortestPath> paths;

    sf::Font font;
};



#endif
