#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Point.h"
#include <SFML/Graphics.hpp>







class Player {

public:
	Player() = default;
	Player(const sf::Texture& tex);

	void drawPlayer(sf::RenderWindow& window);

	void setPoint(Point);
	Point getPoint();

	void newLocation(float x, float y);
	void turnShip();

	void update(float);




private:

	float xcoord;
	float ycoord;
	Point point;

	float targetX = 1e9;
	float targetY = 1e9;

	int idx = 0;
	float anim_timer = 0;
	float anim_speed = 0.23;

	sf::CircleShape ship;

	sf::Sprite sprite;







};





























#endif