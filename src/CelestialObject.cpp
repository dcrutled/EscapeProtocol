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
    anim_speed = radius / 25;


    if (inMass <= 2500) {
        //type = CelestialType::TERRA;
        
        sprite.setOrigin({ 50, 50 });
        sprite.setScale({ .03f * radius, .03f * radius });

    }

    else if (inMass > 2500 && inMass <= 5000) {
        //type = CelestialType::SUPERPLANET;
        
        sprite.setOrigin({ 50, 50 });
        sprite.setScale({ .03f * radius, .03f * radius });
    }

    else if (inMass > 5000 && inMass <= 8000) {
        //type = CelestialType::GASGIANT;
        
        if (sprite.getTexture().getSize().x == 15000) {
            sprite.setOrigin({ 150, 150 });
            sprite.setScale({ .028f * radius, .028f * radius });
            rings = true;
        }

        else {
            rings = false;
            sprite.setOrigin({ 50, 50 });
            sprite.setScale({ .03f * radius, .03f * radius });
        }
    }

    else if (inMass > 8000 && inMass <= 10000) {
       // type = CelestialType::STAR;
        
        sprite.setOrigin({ 100, 100 });
        sprite.setScale({ .033f * radius, .033f * radius });
    }

	



 
    //anim_speed = radius / 32;
       
    //sprite.setScale({ .03f * radius, .03f * radius });

   
    
 
    //sprite.setOrigin({ 50, 50 });

    

 
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

void CelestialObject::drawCelest(sf::RenderWindow& window) {

        //update();

    if (mass <= 2500) {
        //type = CelestialType::TERRA;
        sprite.setTextureRect(sf::IntRect({ idx * 100,0 }, { 100,100 }));
    }

    else if (mass > 2500 && mass <= 5000) {
        //type = CelestialType::SUPERPLANET;
        sprite.setTextureRect(sf::IntRect({ idx * 100,0 }, { 100,100 }));
    }

    else if (mass > 5000 && mass <= 8000) {
        //type = CelestialType::GASGIANT;
        if (rings) {
            sprite.setTextureRect(sf::IntRect({ idx * 300,0 }, { 300,300 }));
        }

        else{ sprite.setTextureRect(sf::IntRect({ idx * 100,0 }, { 100,100 })); }
    }

    else if (mass > 8000 && mass <= 10000) {
        // type = CelestialType::STAR;
        sprite.setTextureRect(sf::IntRect({ idx * 200,0 }, { 200,200 }));
    }


    
        //sprite.setTextureRect(sf::IntRect({ idx * 100,0 }, { 100,100 }));

    
        window.draw(sprite);
  
}

/*
sf::CircleShape CelestialObject::getShape(int i) {
    return celestialObjects[i].shape;
}
*/

