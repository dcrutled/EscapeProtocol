#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <vector>
#include "Point.h"
#include <SFML/Graphics.hpp>


class Enemy {



public:

	Enemy() = default;

	Enemy(const sf::Texture& tex);

	void drawEnemy(sf::RenderWindow& window);

	void setPoint(Point);
	Point getPoint();
	void placeEnemy() { xcoord = point.xcoord; ycoord = point.ycoord; };

	void newLocation(float x, float y);
	void turnEnemy();

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

	sf::CircleShape enemyTest;

	sf::Sprite sprite;


};
















#endif