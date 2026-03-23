#ifndef GAMESPACE_H
#define GAMESPACE_H
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

struct Point {
    string name;
    int position;
    int radius = 0;
    float theta = 0.0;
    float xcoord;
    float ycoord;
};

struct Edge {
    int point;
    //other stuff
};






class GameSpace {

public:

    GameSpace(int ringCount);

    void set_vertices(int vertices);
    int get_vertices() const;

    int get_ringCount() const;

    int get_Degree(int v) const;

    bool checkSymmetry() const;

    void createPointsAndRings(int ringCount);
    void createEdges();
    void makeCartesian();
    void drawMap();

    void polarDistance(struct Point, struct Point);

    void draw(sf::RenderWindow& window);
   




private:
    int vertices;
    int ringCount;
    vector<Point> points;
    vector<vector<Point>> rings;
    vector<vector<int>> edges;
    sf::VertexArray map;
};



#endif
