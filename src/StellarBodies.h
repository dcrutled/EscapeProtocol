#ifndef STELLARBODIES_H
#define STELLARBODIES_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;



struct StellarBody {
	
	string type;

	float xcoord;
	float ycoord;
	float radius;
	float mass;
	float gravity;

	sf::CircleShape shape;

};

















#endif