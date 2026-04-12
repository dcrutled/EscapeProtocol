#include <iostream>
//#include "GameSpace.h"
#include "CelestialObject.h"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;



CelestialObject::CelestialObject(float x, float y, float inMass, const sf::Texture& tex) : sprite(tex){

	xcoord = x;
	ycoord = y;
	mass = inMass;

	radius = pow(mass, (1.f / 2.75));
	gravity = (.087 * mass) / radius;

 
    anim_speed = radius / 32;

    sprite.setScale({ .03f * radius, .03f * radius });

   
    //sprite.setOrigin(sprite.getLocalBounds().size/10000.0f);
 
    sprite.setOrigin({ radius + 30, radius + 30 });

    //sprite.setScale({ .03f * radius, .03f * radius });

 
    sprite.setPosition({xcoord, ycoord});

  

    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(radius, radius));
    shape.setPosition({xcoord, ycoord});
    shape.setFillColor(sf::Color(
        100 + rand() % 256,
        100 + rand() % 256,
        100 + rand() % 256
    ));


}

void CelestialObject::chooseTexture() {





}





void CelestialObject::update(float dt) {

    anim_timer += dt;

    if (anim_timer >= anim_speed) {
        anim_timer = 0;
        idx = (idx + 1) % 50;
    }

    }

void CelestialObject::draw(sf::RenderWindow& window) {

        //update();



        sprite.setTextureRect(sf::IntRect({ idx * 100,0 }, { 100,100 }));


        window.draw(sprite);
  
}

/*
sf::CircleShape CelestialObject::getShape(int i) {
    return celestialObjects[i].shape;
}
*/

