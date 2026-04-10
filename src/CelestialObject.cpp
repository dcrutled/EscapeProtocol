#include <iostream>
#include "GameSpace.h"
#include "CelestialObject.h"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace std;



CelestialObject::CelestialObject(float x, float y, float inMass) {

	xcoord = x;
	ycoord = y;
	mass = inMass;

	radius = pow(mass, (1.f / 2.75));
	gravity = (.087 * mass) / radius;


    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(radius, radius));
    shape.setPosition({ xcoord,ycoord });
    shape.setFillColor(sf::Color(
        100 + rand() % 256,
        100 + rand() % 256,
        100 + rand() % 256
    ));


}


void CelestialObject::update() {

}

void CelestialObject::draw() {

}

/*
sf::CircleShape CelestialObject::getShape(int i) {
    return celestialObjects[i].shape;
}
*/