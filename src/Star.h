#ifndef STAR_H
#define STAR_H
#include <SFML/Graphics.hpp>


struct Star {
	sf::CircleShape shape;
	float twinkleTimer = 0.f;
	float twinkleSpeed = (rand() % 300) / 100.f;
};


#endif