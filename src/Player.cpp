#include <string>
#include <vector>
#include <cmath>
#include <numbers>
#include <SFML/Graphics.hpp>
#include "Player.h"










Player::Player(const sf::Texture& tex) : sprite(tex){


    xcoord = 0;
    ycoord = 0;
    

    sprite.setScale({ .125, .125 });

    sprite.setOrigin({ 256,256 });



    ship.setRadius(10.f);
    ship.setFillColor(sf::Color::Cyan);
    ship.setOrigin(sf::Vector2f(9.5f, 9.f));
    ship.setPosition(sf::Vector2f(xcoord, ycoord));
  
}



void Player::update(float dt) {

    anim_timer += dt;

    if (anim_timer >= anim_speed) {
        anim_timer = 0;
        idx = (idx + 1) % 5;
    }

    if (abs(xcoord - targetX) < 1.f && abs(ycoord - targetY) < 1.f) {
        xcoord = targetX;
        ycoord = targetY;
       

        targetX = 1e9;
        targetY = 1e9;
    }

    else if (targetX != 1e9 && targetY != 1e9) {
       
        xcoord = xcoord + (targetX - xcoord) * 0.02f;
        ycoord = ycoord + (targetY - ycoord) * 0.02f;
       
    }

}



void Player::drawPlayer(sf::RenderWindow& window) {

    //update();

    if (idx == 3) {
        
        sprite.setTextureRect(sf::IntRect({ 0,512 }, { 512,512 }));
    }

    else if (idx == 4) {
        sprite.setTextureRect(sf::IntRect({ 512,512 }, { 512,512 }));
    }

    else {
        sprite.setTextureRect(sf::IntRect({ idx * 512,0 }, { 512,512 }));
    }

    sprite.setPosition({ xcoord, ycoord });
    window.draw(sprite);

}

void Player::newLocation(float x, float y) {

    targetX = x;
    targetY = y;


}

void Player::turnShip() {

    float pi = acos(-1.0);

   
    float angle = atan2(targetY - ycoord, targetX - xcoord) + (pi/2);

    //float angle = acos(dotProduct / (magnitudeCurrent * magnitudeTarget));

    sprite.setRotation({ sf::radians(angle) });


}


void Player::setPoint(Point next) {

    point = next;
}

Point Player::getPoint() {
    return point;
}