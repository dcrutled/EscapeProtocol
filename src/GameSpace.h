#ifndef GAMESPACE_H
#define GAMESPACE_H
#include <string>
#include <vector>
#include <limits>
#include "CelestialObject.h"
#include "Player.h"
#include "Point.h"
#include <SFML/Graphics.hpp>

using namespace std;
/*
struct Point {
    string name;
    int position;
    int ring;
    int radius = 0;
    float theta = 0.0;
    float xcoord;
    float ycoord;
};
*/
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

struct Star {
    sf::CircleShape shape;
    float twinkleTimer = 0.f;
    float twinkleSpeed = (rand() % 300) / 100.f;
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
    void makeBackground();
    void createObstacles();
   
    int calculateGravity(Edge);

    void polarDistance(struct Point, struct Point);

    void draw(sf::RenderWindow& window);
    void inputParse(sf::RenderWindow& window, sf::View&);

    void update(float dt);

    void bellmanFord();


    void testShowStuff();

    void loadAssets();

    
    
   
   




private:
    int vertices;
    int ringCount;
    vector<Point> points;
    vector<vector<Point>> rings;
    vector<vector<int>> edges;
    vector<vector<Edge>> otherEdges;

    //float twinkleTimer = 0.f;
    //float twinkling = .5;
    

    std::unique_ptr<Player> player;

    sf::VertexArray map;

    sf::View defaultView;
    float currentZoom;

    sf::VertexArray farStars;
    //sf::VertexArray nearStars;
    vector<Star> middleStars;
    vector<Star> nearStars;

    sf::Texture playerTex;

    vector<CelestialObject> celestialObjects;

    //vector<sf::Texture> planets;
    vector<unique_ptr<sf::Texture>> planets;
    vector<unique_ptr<sf::Texture>> gasGiants;
    vector<unique_ptr<sf::Texture>> stars;

    vector<ShortestPath> paths;

    sf::Font font;
};



#endif
