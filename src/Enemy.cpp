#include <string>
#include <vector>
#include <cmath>
#include <numbers>
#include <SFML/Graphics.hpp>
#include "Enemy.h"





Enemy::Enemy(const sf::Texture& tex) : sprite(tex) {

    


    xcoord = 0;
    ycoord = 0;


    sprite.setScale({ .175, .175 });

    sprite.setOrigin({ 256,256 });



    enemyTest.setRadius(10.f);
    enemyTest.setFillColor(sf::Color::Cyan);
    enemyTest.setOrigin(sf::Vector2f(9.5f, 9.f));
    enemyTest.setPosition(sf::Vector2f(xcoord, ycoord));

}

int Enemy::getMoves() {
    return totalMoves;
}

void Enemy::update(float dt) {

    anim_timer += dt;

    if (anim_timer >= anim_speed) {
        anim_timer = 0;
        idx = (idx + 1) % 5;
    }

    if (abs(xcoord - targetX) < 5.f && abs(ycoord - targetY) < 5.f) {
        xcoord = targetX;
        ycoord = targetY;

        

       
        setPoint(nextPoint);

        

        targetX = 1e9;
        targetY = 1e9;

        if(totalMoves % 2 == 1) { moveEnemy(); }

        

        
    }

    else if (targetX != 1e9 && targetY != 1e9) {
        xcoord = xcoord + (targetX - xcoord) * 0.015f;
        ycoord = ycoord + (targetY - ycoord) * 0.015f;
        setPoint(nextPoint);

    }

}


void Enemy::drawEnemy(sf::RenderWindow& window) {

    //update();

    if (idx == 3) {

        sprite.setTextureRect(sf::IntRect({ 0,512 }, { 512,512 }));
    }

    else if (idx == 4) {
        sprite.setTextureRect(sf::IntRect({ 512,512 }, { 512,512 }));
    }

    else if (idx == 5) {
        sprite.setTextureRect(sf::IntRect({ 1024,512 }, { 512,512 }));
    }

    else {
        sprite.setTextureRect(sf::IntRect({ idx * 512,0 }, { 512,512 }));
    }

    sprite.setPosition({ xcoord, ycoord });
    window.draw(sprite);

}

void Enemy::newLocation(float x, float y) {

    targetX = x;
    targetY = y;


}

void Enemy::turnEnemy() {

    float pi = acos(-1.0);


    float angle = atan2(targetY - ycoord, targetX - xcoord) + (pi / 2);

    //float angle = acos(dotProduct / (magnitudeCurrent * magnitudeTarget));

    sprite.setRotation({ sf::radians(angle) });


}


void Enemy::setPoint(Point next) {

    point = next;
}

Point Enemy::getPoint() {
    return point;
}


void Enemy::findPlayer(const vector<ShortestPath>& paths, const vector<Point>& points, Point target) {

    //Point target = 
    //pathToPlayer.push();
    Point current = target;
    int next;

    pathToPlayerDrawing.clear();
    pathToPlayer.clear();

    //std::cout << "findPlayer: target=" << target.position
    //    << " enemy point=" << point.position << "\n";


    while (current.position != point.position) {

        if (paths[current.position].parent == -1) {
           // std::cout << "  early return at " << current.position << "\n";
            return;
        }

        pathToPlayerDrawing.push(sf::Vector2f(points[current.position].xcoord, points[current.position].ycoord));
        //std::cout << "  pushing " << current.position << "\n";

        pathToPlayer.push(points[current.position]);

        next = paths[current.position].parent;
        current = points[next];

    }
    //std::cout << "  final push (enemy): " << point.position << "\n";
    pathToPlayerDrawing.push(sf::Vector2f(points[point.position].xcoord, points[point.position].ycoord));

    //return pathPoints;

}

void Enemy::drawPathToPlayer(sf::RenderWindow& window) {

    if (pathToPlayerDrawing.isEmpty()) return;

    sf::VertexArray pathLine(sf::PrimitiveType::LineStrip);

    while (!pathToPlayerDrawing.isEmpty()) {

    

        pathLine.append(sf::Vertex{ pathToPlayerDrawing.peek(), sf::Color::Red });
        pathToPlayerDrawing.pop();
    }

    window.draw(pathLine);
}


Stack<sf::Vector2f> Enemy::getPathToPlayer() {
    return pathToPlayerDrawing;

}



void Enemy::moveEnemy() {
      
    if (pathToPlayer.isEmpty()) return;

    
    if (targetX == 1e9 && targetY == 1e9) {
        ++totalMoves;
        
        nextPoint = pathToPlayer.peek();
        //setPoint(nextPoint);
        targetX = nextPoint.xcoord;
        targetY = nextPoint.ycoord;
        
        pathToPlayer.pop();
        turnEnemy();

        
    }

    
    
}
