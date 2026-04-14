#include <iostream>
#include "GameSpace.h"
#include "CelestialObject.h"
#include "Player.h"
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


void GameSpace::loadAssets() {

    for (auto& entry : filesystem::directory_iterator("assets/Planets/")) {

       // auto planet_sheet = make_unique<sf::Texture>();;
        auto texture = std::make_unique<sf::Texture>();
        if (texture->loadFromFile(entry.path().string())) {
            planets.push_back(std::move(texture));
        }
      
    }


    for (auto& entry : filesystem::directory_iterator("assets/Gas Giants/")) {

        // auto planet_sheet = make_unique<sf::Texture>();;
        auto texture = std::make_unique<sf::Texture>();
        if (texture->loadFromFile(entry.path().string())) {
            gasGiants.push_back(std::move(texture));
        }
      
    }

    for (auto& entry : filesystem::directory_iterator("assets/Stars/")) {

        // auto planet_sheet = make_unique<sf::Texture>();;
        auto texture = std::make_unique<sf::Texture>();
        if (texture->loadFromFile(entry.path().string())) {
            stars.push_back(std::move(texture));
        }

    }


    playerTex.loadFromFile("assets/Player/Spike_SpriteSheet.png");

    player = std::make_unique<Player>(playerTex);



    enemyTex.loadFromFile("assets/Enemy/Alien Frigate.png");

    enemy = std::make_unique<Enemy>(enemyTex);

}




GameSpace::GameSpace(int ringCount) {
    loadAssets();//gamespace constructor
    this -> ringCount = ringCount;
    createPointsAndRings(ringCount);
    int vertices = points.size();
    set_vertices(vertices);
    createEdges();
    
    makeBackground();
    createObstacles();
    //bellmanFord();
    testShowStuff();
    
    drawMap();
    makeBackground();
   

}

void GameSpace::inputParse(sf::RenderWindow& window, sf::View& view) {

    while (const std::optional event = window.pollEvent())
    {

        //------------------------------------------------------------------------


        if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>())
        {
            // Convert mouse pixel position to world coordinates
            sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

            float zoomFactor = (scroll->delta > 0) ? 0.9f : 1.1f;

            if (view.getSize().x > 4000 && view.getSize().y > 2500) {
                zoomFactor = (scroll->delta > 0) ? 0.9f : 1.0;
            }


            view.zoom(zoomFactor);

            // After zooming, shift the view center toward the mouse position
            sf::Vector2f newMouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
            view.move(mouseWorld - newMouseWorld);

            window.setView(view);
        }


        //------------------------------------------------------------------------

        if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
        {
            // Convert mouse pixel position to world coordinates
            sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

            /*

            for (auto& point : points) {


                if (abs(mouseWorld.x - point.xcoord) < 10 && abs(mouseWorld.y - point.ycoord) < 10) {

                    if (player->getPoint().ring <= point.ring && abs(player->getPoint().ring - point.ring) <= 1) {
                        player->newLocation(point.xcoord, point.ycoord);

                        player->turnShip();

                        player->setPoint(point);
                    }
                }


            }
            */

            float clickDistance = sqrt((pow((mouseWorld.x - player->getPoint().xcoord), 2)) + (pow((mouseWorld.y - player->getPoint().ycoord), 2)));

            for (auto& edge : otherEdges) {

                for (int i = 0; i < edge.size(); i++) {

                    if (edge[i].point1.xcoord == player->getPoint().xcoord && edge[i].point1.ycoord == player->getPoint().ycoord) {

                        //std::cout << "Passed the same start check.\n";

                        float checkDistance = sqrt((pow((edge[i].point2.xcoord - player->getPoint().xcoord), 2)) + (pow((edge[i].point2.ycoord - player->getPoint().ycoord), 2)));

                        if (abs(checkDistance - clickDistance) <= 20 
                            && (abs(mouseWorld.x - edge[i].point2.xcoord) < 10 && abs(mouseWorld.y - edge[i].point2.ycoord) < 10)
                            && (player->getPoint().ring <= edge[i].point2.ring && abs(player->getPoint().ring - edge[i].point2.ring) <= 1)) {


                            player->newLocation(edge[i].point2.xcoord, edge[i].point2.ycoord);

                            player->turnShip();

                            player->setPoint(edge[i].point2);

                            break;


                        }




                    }
                }
            }



            //player->newLocation(mouseWorld.x, mouseWorld.y);

            //player->point();


        }


        //------------------------------------------------------------------------


        if (event->is<sf::Event::Closed>())
            window.close();
    }








    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        if (view.getCenter().y < -500.f) {
            view.move({ 0,0 });
            //window.setView(view);
        }
        else {
            view.move({ 0, -2.f });
            //window.setView(view);
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        if (view.getCenter().y > 500.f) {
            view.move({ 0,0 });
            //window.setView(view);
        }
        else {
            view.move({ 0, 2.f });
            //window.setView(view);
        }


    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if (view.getCenter().x < -500.f) {
            view.move({ 0,0 });
            //window.setView(view);
        }
        else {
            view.move({ -2.f, 0 });
            //window.setView(view);
        }


    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if (view.getCenter().x > 500.f) {
            view.move({ 0,0 });
            //window.setView(view);
        }
        else {
            view.move({ 2.f, 0 });
            //window.setView(view);
        }
    }


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
    //rings.resize(j + 1);     //ring count is resized to account for the origin point
    float pi = 2 * acos(0);

    for (int h = 0; h <= j; h++) {
        vector<Point> tempRing;


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
            tempRing.push_back(point);
            rings.push_back(tempRing);
            //rings[0].push_back(point);
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
            point.ring = h;
            //points.push_back(vector<Point>());

            int holding = points.size();
            string name = "p" + to_string(holding);
            point.name = name;

            point.radius = h;
            point.position = points.size();          //initialize point name, radius (based on ring), and position in line (vertex name as an int)


            if (h % 2 == 0) {                        //even rings are offset
                if (i == 1) {
                    point.theta = (i * pi) / (pow(2, (k)));
                    //point.ring = h + 1;
                    points.push_back(point);
                    tempRing.push_back(point);
                    //rings[h].push_back(point);
                    continue;
                }

                point.theta = points[points.size() - 1].theta + ((pi) / (pow(2, (k - 1))));

            }

            else if (h % 2 == 1) {                  //odd rings have a point with theta == 0


                if (i == 1) {
                    point.theta = 0;
                    points.push_back(point);
                    //point.ring = h + 1;
                    tempRing.push_back(point);
                    //rings[h].push_back(point);
                    continue;
                }
                point.theta = points[points.size() - 1].theta + (pi) / (pow(2, (k - 1)));
            }

            //point.ring = h;
            points.push_back(point);
            tempRing.push_back(point);
            //rings[h].push_back(point);

        }

        rings.push_back(tempRing);
        //points[1].ring = 1;
        //if (points.size() > 25) points[25].ring = 5;

        /*
        for (int i = 0; i < points.size(); i++) {
            std::cout << "Point " << i << " -> ring " << points[i].ring << std::endl;
        }*/

    }
    
    makeCartesian();
    player->setPoint(points[0]);
    int idx = rand() % rings[ringCount].size();
    enemy->setPoint(points[rings[ringCount][idx].position]);
    enemy->placeEnemy();

    
    
    //END OF FOR LOOP FOR POINT CREATION ----------------- UNCOMMENT BLOCK BELOW IF YOU WANT TO CHECK INDIVIDUAL POINT COORDINATES
    /*
    for (int i = 0; i < size(points); i++) {
        cout << points[i].name << "   (" << points[i].xcoord << ", " << points[i].ycoord << ")" << endl;
    }*/

    cout << points[size(points) - 1].name << "   (" << points[size(points) - 1].xcoord << ", " << points[size(points) - 1].ycoord << ")" << endl;


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
            temp.endRing = points[edges[i][k]].ring;

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

            v1.color = sf::Color(255, 255, 255, 100);
            v2.color = sf::Color(255, 255, 255, 100);


            map.append(v1);
            map.append(v2);
        }
    }

    
}


void GameSpace::update(float dt) {

    for (auto& obj : celestialObjects) {
        obj.update(dt);
    }

    player->update(dt);
    enemy->update(dt);

    for (auto& star : middleStars) {
        star.twinkleTimer += dt;
    }

    for (auto& star : nearStars) {
        star.twinkleTimer += dt;
    }


}



void GameSpace::draw(sf::RenderWindow& window)
{


    window.draw(map);
    window.draw(farStars);

    for (auto& star : middleStars) {
        /*

        if (star.twinkleTimer >= star.twinkleSpeed) {
            int alphaValue = rand() % 256;
            star.shape.setFillColor({ 255, 255, 255, static_cast<uint8_t>(alphaValue) });
            star.twinkleTimer = 0;
            
            }
        */
        float alpha = 177.5f + sin(star.twinkleTimer * star.twinkleSpeed) * 77.5f;
        star.shape.setFillColor({ 255, 255, 255, static_cast<uint8_t>(alpha) });
        window.draw(star.shape);
    }
    for (auto& star : nearStars) {
        /*
        if (star.twinkleTimer >= star.twinkleSpeed) {

            int alphaValue = rand() % 256;
            star.shape.setFillColor({ 255, 255, 255, static_cast<uint8_t>(alphaValue) });
            star.twinkleTimer = 0;

        }
        */
        float alpha = 177.5f + sin(star.twinkleTimer * star.twinkleSpeed) * 77.5f;
        star.shape.setFillColor({ 255, 255, 255, static_cast<uint8_t>(alpha) });
        window.draw(star.shape);
    }


    for (auto& obj : celestialObjects) {
        obj.drawCelest(window);
        //sf::CircleShape debugDot(10.f);
        //debugDot.setFillColor(sf::Color::Red);
        //debugDot.setOrigin(sf::Vector2f(9.5f, 9.f));
        //debugDot.setPosition(sf::Vector2f(obj.getX(), obj.getY()));
        //window.draw(debugDot);
    }

 
    
    //int idx = rand() % rings[ringCount].size();
    //Point testP = points[rings[ringCount][idx].position];

    sf::CircleShape debugDot(10.f);
    debugDot.setFillColor(sf::Color::Red);
    debugDot.setRadius(10);
    debugDot.setOrigin(sf::Vector2f(10, 10));
    debugDot.setPosition(sf::Vector2f(0, 0));
    //window.draw(debugDot);
    
   
    for (int i = 0; i < points.size(); i++) {
      



        sf::Text text(font);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::White);

        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1.f);

        float x = points[i].xcoord;
        float y = points[i].ycoord;

    


        text.setPosition(sf::Vector2f(x, y));
        text.setString(std::to_string(i));

        sf::FloatRect bounds = text.getGlobalBounds();

        text.setPosition({
            points[i].xcoord - bounds.size.x / 2.f,
            points[i].ycoord - bounds.size.y / 2.f - 2.f
            });

        text.setStyle(sf::Text::Bold);

        window.draw(text);
        window.draw(text);
    }
    player->drawPlayer(window);
    enemy->drawEnemy(window);

    for (int i = 0; i < otherEdges.size(); i++) {

        for (int k = 0; k < otherEdges[i].size(); k++) {

            if (otherEdges[i][k].point2.ring < otherEdges[i][k].point1.ring || otherEdges[i][k].weight == 0) {
                continue;
            }

            else {


                sf::Text text(font);
                text.setCharacterSize(20);
                text.setFillColor(sf::Color(255, 215, 0));
                if(otherEdges[i][k].point2.ring == otherEdges[i][k].point1.ring){ text.setFillColor(sf::Color(0,255,255,50)); }

                float x = (otherEdges[i][k].point1.xcoord + otherEdges[i][k].point2.xcoord) / 2;
                float y = (otherEdges[i][k].point1.ycoord + otherEdges[i][k].point2.ycoord) / 2;

                text.setPosition(sf::Vector2f(x - 10, y));
                text.setString(std::to_string(otherEdges[i][k].weight));

                window.draw(text);
                window.draw(text);
            }
        }
    }
    
    

   
}


//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------


void GameSpace::createObstacles() {

    
    int k;


    if (!font.openFromFile("assets/fonts/JLSDataGothicC_NC.otf")) {
        std::cout << "FAILED\n";
    }


    //srand(time(0));

    for (int i = 1; i < ringCount; i++) {

        

        k = rand() % rings[i].size();



        
        float xcoord = points[rings[i][k].position].xcoord;
        float ycoord = points[rings[i][k].position].ycoord;


        //cout << k << " (" << points[rings[i][k].position].xcoord << ", " << points[rings[i][k].position].ycoord << ")" << endl;


        
        float mass = rand() % 10001;

        

        if (mass <= 2500) {
            const sf::Texture& tex = *planets[rand() % planets.size()];
            CelestialObject body(xcoord, ycoord, mass, tex);
            celestialObjects.push_back(body);
        }

        else if (mass > 2500 && mass <= 5000) {
            const sf::Texture& tex = *planets[rand() % planets.size()];
            CelestialObject body(xcoord, ycoord, mass, tex);
            celestialObjects.push_back(body);
        }

        else if (mass > 5000 && mass <= 8000) {
            const sf::Texture& tex = *gasGiants[rand() % gasGiants.size()];
            CelestialObject body(xcoord, ycoord, mass, tex);
            celestialObjects.push_back(body);
        }

        else if (mass > 8000 && mass <= 10000) {
            const sf::Texture& tex = *stars[rand() % stars.size()];
            CelestialObject body(xcoord, ycoord, mass, tex);
            celestialObjects.push_back(body);
        }

        

        //sf::Texture tex = planets[rand() % planets.size() + 1];
        //const sf::Texture& tex = *planets[rand() % planets.size()];

       // CelestialObject body(xcoord, ycoord, mass, tex);
        //celestialObjects.push_back(body);




    }

    for (int i = 0; i < otherEdges.size(); i++) {


        for (int k = 0; k < otherEdges[i].size(); k++) {

            if (otherEdges[i][k].point2.ring < otherEdges[i][k].point1.ring) {
                continue;
            }

            else if (otherEdges[i][k].point2.ring == otherEdges[i][k].point1.ring) {
                int u = otherEdges[i][k].point1.position;
                int v = otherEdges[i][k].point2.position;

                if (u < v) {
                    int w = calculateGravity(otherEdges[i][k]);

                    // assign to both directions
                    otherEdges[i][k].weight = w;

                    // find reverse edge and assign same weight
                    for (auto& e : otherEdges[v]) {
                        if (e.point2.position == u) {
                            e.weight = w;
                            break;
                        }
                    }
                }


                else {
                    continue;
                }
            }

            else {
                otherEdges[i][k].weight = calculateGravity(otherEdges[i][k]);
            }


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

    for (int i = 0; i < otherEdges.size(); i++) {
        cout << "Point (" << otherEdges[i][0].point1.position << ") " << endl;

        for (int k = 0; k < otherEdges[i].size(); k++) {


            cout << "\tP(" << otherEdges[i][k].point1.position << ") to P(" << otherEdges[i][k].point2.position << ")  Ring: " << otherEdges[i][k].endRing << endl;



        }

    }


    bellmanFord(enemy->getPoint().position);

    for (int i = 0; i < paths.size(); i++) {
        cout << "Distance to: " << i << " = " << paths[i].distance << endl;
        //cout << "Parent of: " << i << " is " << paths[i].parent << endl;
    }

    


}



int GameSpace::calculateGravity(Edge temp) {

    float totalGrav = 0;

    //cout << "\n\n\n\n";

    //cout << "RING COUNT: " << ringCount << "\n";
    //cout << "STELLAROBJECTS SIZE: " << stellarObjects.size() << "\n";
    //cout << "CELESTIALOBJECTS SIZE: " << celestialObjects.size();

    //cout << "\n\n\n\n";

    for (int i = 0; i < celestialObjects.size(); i++) {
        float grav;


        float d1 = sqrt((pow((celestialObjects[i].getX() - temp.point1.xcoord), 2)) + (pow((celestialObjects[i].getY() - temp.point1.ycoord), 2)));
        float d2 = sqrt((pow((celestialObjects[i].getX() - temp.point2.xcoord), 2)) + (pow((celestialObjects[i].getY() - temp.point2.ycoord), 2)));

        if (temp.point2.ring == temp.point1.ring) {
            int ave = (d1 + d2) / 2;
            grav = (.087 * 10 * celestialObjects[i].getMass()) / (ave);
            totalGrav = totalGrav + grav;
            continue;
        }

        //if (d2 < 50) { d2 = 50; };

        
        else if (d2 > d1) {
            grav = (.087 * 10 * celestialObjects[i].getMass()) / (d2 + 50);
        }

        else {
            grav = (.037 * 10 * celestialObjects[i].getMass() *-1) / (d2 + 50);
        }

        totalGrav = totalGrav + grav;

    }
    /*
    if (!std::isfinite(totalGrav)) {
        std::cout << "BAD GRAVITY: "
            << temp.point1.position << " -> "
            << temp.point2.position << std::endl;
        return 0;  // safe fallback
    }*/

    int weight = (int)totalGrav;

    return weight;

}


//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------




void GameSpace::bellmanFord(int loc) {
    //ShortestPath initial;
    paths.resize(points.size());
    //paths.push_back(initial);
    paths[loc].distance = 0;




    for (int i = 0; i < points.size(); i++) {

        for (int k = 0; k < otherEdges.size(); k++) {

            for (auto& e : otherEdges[k]) {

            


                if (e.point1.ring <= e.point2.ring) {
                    cout << " Enemy ring greater than player\n";
                    //cout << "Good" << endl;
                    /*
                    if (paths[e.point1.position].distance + e.weight < paths[e.point2.position].distance) {
                        paths[e.point2.position].distance = paths[e.point1.position].distance + e.weight;
                        paths[e.point2.position].parent = e.point1.position;
                    }
                    */
                    if (paths[e.point2.position].distance + e.weight < paths[e.point1.position].distance) {
                        paths[e.point1.position].distance = paths[e.point2.position].distance + e.weight;
                        paths[e.point1.position].parent = e.point2.position;
                    }

                    else { continue; }
                    }

                else {
                    continue;
                }
            }
        }
    }



}




void GameSpace::makeBackground() {

    farStars = sf::VertexArray(sf::PrimitiveType::Points);

    for (int i = 0; i < 800; i++) {
        
        sf::Vertex v;
        float x = (rand() % 6000) - 3000;
        float y = (rand() % 4500) - 2250;

        v.position = sf::Vector2f(x,y);

        farStars.append(v);

    }


    for (int i = 0; i < 300; i++) {

        Star star;

        

        star.shape.setRadius(1.0f);

        float x = (rand() % 6000) - 3000;
        float y = (rand() % 4500) - 2250;

        star.shape.setPosition({ x, y });

        middleStars.push_back(star);

    }


    for (int i = 0; i < 200; i++) {

        Star star;

        

        star.shape.setRadius(2.0f);

        float x = (rand() % 6000) - 3000;
        float y = (rand() % 4500) - 2250;

        star.shape.setPosition({ x, y });

        nearStars.push_back(star);

    }


}