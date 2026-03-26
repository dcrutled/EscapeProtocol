#include <iostream>
#include "GameSpace.h"
#include "StellarBodies.h"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace std;


void GameSpace::set_vertices(int vertices) {
    this->vertices = vertices;
}

int GameSpace::get_vertices() const {
    return vertices;
}

int GameSpace::get_ringCount() const {
    return ringCount;
}

int GameSpace::get_Degree(int v) const {
    return edges[v].size();
}

bool GameSpace::checkSymmetry() const {    //checks each edge vector for each vertex. if match is found, it makes a direct reverse check to confirm symmetry.
    bool symmetry = true;

    for (int h = 0; h < edges.size(); h++) {
       

        for (int i = 0; i < edges.size(); i++) {

            int cnt = count(edges[i].begin(), edges[i].end(), h); //initial value check

            if (cnt > 0) {
                int cnt2 = count(edges[h].begin(), edges[h].end(), i); //reverse check to confirm symmetry

                if (cnt2 == cnt) {
                    continue;
                }

                else if (cnt2 != cnt) {
                    cout << "Symmetry Error Found! " << h << " and " << i << " are not symmetric." << endl;
                    symmetry = false;
                }
            }
            else {
                continue;
            }

        }
        cout << "Symmetry Confirmed" << endl;
    }

    return symmetry;

}

GameSpace::GameSpace(int ringCount) {   //gamespace constructor
    this -> ringCount = ringCount;
    createPointsAndRings(ringCount);
    int vertices = points.size();
    set_vertices(vertices);
    createEdges();
    createObstacles();
    testShowStuff();
    drawMap();
   

}


void GameSpace::polarDistance(struct Point p1, struct Point p2) { //converts polar coordinates to cartesion the computes distance
    float x1 = p1.radius * cos(p1.theta);
    float x2 = p2.radius * cos(p2.theta);

    float y1 = p1.radius * sin(p1.theta);
    float y2 = p2.radius * sin(p2.theta);

    double distance = sqrt((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));

    //cout << "Distance between " << p1.name << " and " << p2.name<< " is:  " << distance << endl;


}


void GameSpace::createPointsAndRings(int ringCount) {

    int j = ringCount;   
    rings.resize(j + 1);     //ring count is resized to account for the origin point
    float pi = 2 * acos(0);

    for (int h = 0; h <= j; h++) {

        int k;


        if (h == 0) {        //initialize origin


            Point point;
            point.name = "p0";
            point.position = 0;
            point.ring = 0;
            point.radius = 0;
            point.theta = 0;
            //points.push_back(vector<Point>());
            points.push_back(point);
            rings[0].push_back(point);
            continue;
        }

        if (h % 2 == 1) {        //determines number of points in a given ring for the loop below this
            k = h + 1;           //rings r0: 1, r1: 4, r2: 4, r3: 8, r4: 8, r5: 16 etc (powers of 2)
            k = k / 2;
            k = k + 1;
        }

        else if (h % 2 == 0) {
            k = h / 2;
            k = k + 1;
        }

        for (int i = 1; i <= pow(2, k); i++) {

            Point point;
            //points.push_back(vector<Point>());

            int holding = points.size();
            string name = "p" + to_string(holding);
            point.name = name;

            point.radius = h;
            point.position = points.size();          //initialize point name, radius (based on ring), and position in line (vertex name as an int)


            if (h % 2 == 0) {                        //even rings are offset
                if (i == 1) {
                    point.theta = (i * pi) / (pow(2, (k)));
                    points.push_back(point);
                    rings[h].push_back(point);
                    continue;
                }

                point.theta = points[points.size() - 1].theta + ((pi) / (pow(2, (k - 1))));

            }

            else if (h % 2 == 1) {                  //odd rings have a point with theta == 0


                if (i == 1) {
                    point.theta = 0;
                    points.push_back(point);
                    rings[h].push_back(point);
                    continue;
                }
                point.theta = points[points.size() - 1].theta + (pi) / (pow(2, (k - 1)));
            }

            point.ring = h;
            points.push_back(point);
            rings[h].push_back(point);

        }


    }
    
    makeCartesian();
    
    //END OF FOR LOOP FOR POINT CREATION ----------------- UNCOMMENT BLOCK BELOW IF YOU WANT TO CHECK INDIVIDUAL POINT COORDINATES

    for (int i = 0; i < size(points); i++) {
        cout << points[i].name << "   (" << points[i].xcoord << ", " << points[i].ycoord << ")" << endl;
    }


}




void GameSpace::createEdges() {

    edges.resize(points.size());


    for (int i = 0; i < rings.size(); i++) {


        //-------------RING 0--------------------------------------------------------------------------------------------------------------
        if (i == 0 && rings.size() > 1) {
            edges[i].push_back(1);
            edges[i].push_back(2);
            edges[i].push_back(3);
            edges[i].push_back(4);
        }

        //---------------------------------------------------------------------------------------------------------------------------------
        //-------------RING 1 -------------------------------------------------------------------------------------------------------------
        else if (i == 1) {
            for (int k = 0; k < rings[i].size(); k++) {
                //std::cout << "i: " << i << " k: " << k << std::endl;
                edges[rings[i][k].position].push_back(0);

                edges[rings[i][k].position].push_back(rings[i][(k - 1) % rings[i].size()].position);
                edges[rings[i][k].position].push_back(rings[i][(k + 1) % rings[i].size()].position);

                if (i != rings.size() - 1) {
                    edges[rings[i][k].position].push_back(rings[i + 1][(k - 1) % rings[i + 1].size()].position);
                    edges[rings[i][k].position].push_back(rings[i + 1][k].position);
                }

            }
        }
        //----------------------------------------------------------------------------------------------------------------------------------
        //-------------------------RINGS WHOSE SIZE DOES NOT MATCH THAT OF THE NEXT RING----------------------------------------------------
        else if ((i != rings.size() - 1) &&
            ((rings[i + 1].size() / rings[i].size()) == 2)
            ) {


            for (int k = 0; k < rings[i].size(); k++) {
                //std::cout << "i: " << i << " k: " << k << std::endl;

                edges[rings[i][k].position].push_back(rings[i][(k - 1) % rings[i].size()].position);
                edges[rings[i][k].position].push_back(rings[i][(k + 1) % rings[i].size()].position);

                edges[rings[i][k].position].push_back(rings[i - 1][k].position);
                edges[rings[i][k].position].push_back(rings[i - 1][(k + 1) % rings[i - 1].size()].position);



                edges[rings[i][k].position].push_back(rings[i + 1][(2 * k) % rings[i + 1].size()].position);
                edges[rings[i][k].position].push_back(rings[i + 1][((2 * k) + 1) % rings[i + 1].size()].position);
                edges[rings[i][k].position].push_back(rings[i + 1][((2 * k) + 2) % rings[i + 1].size()].position);

            }
        }
        //----------------------------------------------------------------------------------------------------------------------------------
        //------------------------RING WHOSE SIZE MATCHES THE NEXT RING---------------------------------------------------------------------

        else if ((i != rings.size() - 1) &&
            ((rings[i + 1].size() / rings[i].size()) == 1)
            ) {


            for (int k = 0; k < rings[i].size(); k++) {
                //std::cout << "i: " << i << " k: " << k << std::endl;


                if (k % 2 == 0) {
                    //(Ring + 1) / (R) == 1 --- R[k].position % 2 == 0

                    edges[rings[i][k].position].push_back(rings[i][(k - 1) % rings[i].size()].position);
                    edges[rings[i][k].position].push_back(rings[i][k].position + 1);

                    edges[rings[i][k].position].push_back(rings[i - 1][k / 2].position);
                    edges[rings[i][k].position].push_back(rings[i - 1][((k / 2) - 1) % rings[i - 1].size()].position);

                    edges[rings[i][k].position].push_back(rings[i + 1][k].position);
                    edges[rings[i][k].position].push_back(rings[i + 1][(k - 1) % rings[i + 1].size()].position);
                }

                else if (k % 2 == 1) {
                    edges[rings[i][k].position].push_back(rings[i][(k - 1) % rings[i].size()].position);
                    edges[rings[i][k].position].push_back(rings[i][(k + 1) % rings[i].size()].position);

                    edges[rings[i][k].position].push_back(rings[i - 1][(k - 1) / 2].position);

                    edges[rings[i][k].position].push_back(rings[i + 1][(k - 1) % rings[i + 1].size()].position);
                    edges[rings[i][k].position].push_back(rings[i + 1][k].position);

                }

            }
        }


        //----------------------------------------------------------------------------------------------------------------------------------
        //----------------------IF LAST RING IS ONE WHOSE SIZE IS DIFFERENT THAN THE PREVIOUS RING------------------------------------------


        else if (i == rings.size() - 1 && (rings[i].size() / rings[i - 1].size()) == 2) {

            for (int k = 0; k < rings[i].size(); k++) {
                //std::cout << "i: " << i << " k: " << k << std::endl;


                if (k % 2 == 0) {
                    //(Ring + 1) / (R) == 1 --- R[k].position % 2 == 0

                    edges[rings[i][k].position].push_back(rings[i][(k - 1) % rings[i].size()].position);
                    edges[rings[i][k].position].push_back(rings[i][k].position + 1);

                    edges[rings[i][k].position].push_back(rings[i - 1][k / 2].position);
                    edges[rings[i][k].position].push_back(rings[i - 1][((k / 2) - 1) % rings[i - 1].size()].position);

                }

                else if (k % 2 == 1) {
                    edges[rings[i][k].position].push_back(rings[i][(k - 1) % rings[i].size()].position);
                    edges[rings[i][k].position].push_back(rings[i][(k + 1) % rings[i].size()].position);

                    edges[rings[i][k].position].push_back(rings[i - 1][(k - 1) / 2].position);

                }

            }
        }

        //----------------------------------------------------------------------------------------------------------------------------------
        //----------------------IF LAST RING IS ONE WHOSE SIZE IS THE SAME AS THE PREVIOUS RING --------------------------------------------

        else if (i == rings.size() - 1 && (rings[i].size() / rings[i - 1].size()) == 1) {

            for (int k = 0; k < rings[i].size(); k++) {
                //std::cout << "i: " << i << " k: " << k << std::endl;

                edges[rings[i][k].position].push_back(rings[i][(k - 1) % rings[i].size()].position);
                edges[rings[i][k].position].push_back(rings[i][(k + 1) % rings[i].size()].position);


                edges[rings[i][k].position].push_back(rings[i - 1][k].position);
                edges[rings[i][k].position].push_back(rings[i - 1][(k + 1) % rings[i].size()].position);

            }
        }
        //----------------------------------------------------------------------------------------------------------------------------------
    }

    otherEdges.resize(edges.size());

    for (int i = 0; i < edges.size(); i++) {

        cout << "p" << i << ":  ";

        for (int k = 0; k < edges[i].size(); k++) {

            Edge temp;
            temp.point1 = points[i];
            temp.point2 = points[edges[i][k]];

            otherEdges[i].push_back(temp);

            cout << "(" << edges[i][k] << ")  ";
        }
        cout << endl;
    }

    /*

    //Temporary addition for professor to check symmetry of graph
    string symChoice;
    cout << endl << "Would you like to test the symmetry of your gamespace? Type \"yes\" or \"no\" : ";
    cin >> symChoice;
    if(symChoice == "yes") {
        checkSymmetry();
    }
    */

}

/*

void createGameSpaceGraph(int rings) {

    for (int i = 0; i < VERTICES; i++) {

      

    }

}
*/

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------



void GameSpace::makeCartesian() {

    for (int i = 0; i < points.size(); i++) {
        points[i].xcoord = (points[i].radius * cos(points[i].theta)) * 100; //+ 960;
        points[i].ycoord = (points[i].radius * sin(points[i].theta)) * 100; //+ 540;
    }


}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------


void GameSpace::drawMap() {

    

    
    map = sf::VertexArray(sf::PrimitiveType::Lines);

    for (int i = 0; i < edges.size(); i++)
    {
        for (int k = 0; k < edges[i].size(); k++) {

            sf::Vertex v1;
            sf::Vertex v2;

            v1.position = sf::Vector2f(points[i].xcoord, points[i].ycoord);
            v2.position = sf::Vector2f(points[edges[i][k]].xcoord, points[edges[i][k]].ycoord);


            map.append(v1);
            map.append(v2);
        }
    }

    
}




void GameSpace::draw(sf::RenderWindow& window)
{
    window.draw(map);

    
   
    for (int i = 0; i < points.size(); i++) {
        sf::Text text(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

        float x = points[i].xcoord;
        float y = points[i].ycoord;

        text.setPosition(sf::Vector2f(x + 5.f, y + 5.f));
        text.setString(std::to_string(i));

        window.draw(text);
    }

    for (int i = 0; i < otherEdges.size(); i++) {

        for (int k = 0; k < otherEdges[i].size(); k++) {
            sf::Text text(font);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Green);

            float x = (otherEdges[i][k].point1.xcoord + otherEdges[i][k].point2.xcoord) / 2;
            float y = (otherEdges[i][k].point1.ycoord + otherEdges[i][k].point2.ycoord) / 2;

            text.setPosition(sf::Vector2f(x-10, y));
            text.setString(std::to_string(otherEdges[i][k].weight));

            window.draw(text);
        }
    }
    
    

    for (int i = 0; i < stellarObjects.size(); i++) {
       
        window.draw(stellarObjects[i].shape);
    }
}


//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------


void GameSpace::createObstacles() {
    
    stellarObjects.resize(ringCount);
    int k;

    
    if (!font.openFromFile("assets/fonts/Megrim-Regular.ttf")) {
        std::cout << "FAILED\n";
    }


    //srand(time(0));

    for (int i = 1; i <= ringCount; i++) {

        StellarBody tempBody;

        k = rand() % rings[i].size();

    

        tempBody.xcoord = points[rings[i][k].position].xcoord;
        tempBody.ycoord = points[rings[i][k].position].ycoord;
        //tempBody.point = points[rings[i][k].position];

       

        //cout << k << " (" << points[rings[i][k].position].xcoord << ", " << points[rings[i][k].position].ycoord << ")" << endl;


        tempBody.mass = rand() % 10000;
        tempBody.radius = pow(tempBody.mass, (1.f / 2.75));
        tempBody.gravity = (.087 * tempBody.mass) / tempBody.radius;
        

        tempBody.shape.setRadius(tempBody.radius);
        tempBody.shape.setOrigin(sf::Vector2f(tempBody.radius, tempBody.radius));
        tempBody.shape.setPosition({ tempBody.xcoord,tempBody.ycoord });
        tempBody.shape.setFillColor(sf::Color(
            100 + rand() % 256,
            100 + rand() % 256,
            100 + rand() % 256
        ));

        for (int h = 0; h < edges[rings[i][k].position].size(); h++) {

            otherEdges[rings[i][k].position][h].weight = static_cast<int>(round(tempBody.gravity));
            //cout << "Edge" << otherEdges[rings[i][k].position][h].point1.position << " to " << otherEdges[rings[i][k].position][h].point2.position << ": " << otherEdges[rings[i][k].position][h].weight << endl;

            for (int j = 0; j < edges[otherEdges[rings[i][k].position][h].point2.position].size(); j++) {
                if (otherEdges[otherEdges[rings[i][k].position][h].point2.position][j].weight == 0) {
                    otherEdges[otherEdges[rings[i][k].position][h].point2.position][j].weight = static_cast<int>(round(tempBody.gravity / 2));
                }

                else {
                    otherEdges[otherEdges[rings[i][k].position][h].point2.position][j].weight = otherEdges[otherEdges[rings[i][k].position][h].point2.position][j].weight
                        + static_cast<int>(round(tempBody.gravity)) / 2;
                }
                //cout << "\tEdge" << otherEdges[otherEdges[rings[i][k].position][h].point2.position][j].point1.position << " to " << otherEdges[otherEdges[rings[i][k].position][h].point2.position][j].point2.position << ": " << otherEdges[otherEdges[rings[i][k].position][h].point2.position][j].weight << endl;
            }

            
        }

        stellarObjects.push_back(tempBody);

        //cout << tempBody.radius << endl;


    }


}




void GameSpace::setEdgeWeight(int i, int k, StellarBody tempBody) {

    for (int i = 0; i < otherEdges.size(); i++) {

        for (int k = 0; k < otherEdges[i].size(); k++) {
            otherEdges[i][k].weight = calculateGravity(otherEdges[i][k]);

           // if(otherEdges[otherEdges[i][k].point2.position][])
        }
  }


}


void GameSpace::testShowStuff() {

    for (int i = 0; i < otherEdges.size(); i++) {
        cout << "Point (" << otherEdges[i][0].point1.position << ") " << endl;

        for (int k = 0; k < otherEdges[i].size(); k++) {

            
                cout << "\tP(" << otherEdges[i][k].point1.position << ") to P(" << otherEdges[i][k].point2.position << ")  Weight: " << otherEdges[i][k].weight << endl;



        }

    }


}



int GameSpace::calculateGravity(Edge temp) {

    float totalGrav = 0;

    for (int i = 0; i < stellarObjects.size(); i++) {
        float grav;

        float d1 = sqrt((pow((stellarObjects[i].xcoord - temp.point1.xcoord), 2)) + (pow((stellarObjects[i].ycoord - temp.point1.ycoord), 2)));
        float d2 = sqrt((pow((stellarObjects[i].xcoord - temp.point2.xcoord), 2)) + (pow((stellarObjects[i].ycoord - temp.point2.ycoord), 2)));

        
        if (d2 > d1) {
            grav = (.087 * 10 * stellarObjects[i].mass * -1) / d2;
        }

        else {
            grav = (.087 * 10 * stellarObjects[i].mass) / d2;
        }

        totalGrav = totalGrav + grav;

    }

    int weight = (int)totalGrav;

    return weight;

}