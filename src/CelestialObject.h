#pragma message("USING THIS CELESTIALOBJECT HEADER")
#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;



struct StellarBody {
	
	string type;
	//Point point;

	float xcoord;
	float ycoord;
	float radius;
	float mass;
	float gravity;

	sf::CircleShape shape;

};

enum class CelstialType {
	TERRA,
	SUPERPLANET,
	GASGIANT,
	STAR
};


class CelestialObject {
	//sf::Sprite m_sprite;
public:

	CelestialObject(float x, float y, float inMass, const sf::Texture& tex);
	//sf::CircleShape getShape(int i);

	void chooseTexture();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	float getMass() const { return mass; }
	float getRadius() const { return radius; }
	float getX() const { return xcoord; }
	float getY() const { return ycoord; }

	


private:
	
	float xcoord;
	float ycoord;
	float radius;
	float mass;
	float gravity;

	int idx = 0;
	float anim_timer = 0;
	float anim_speed = 0.23;


	

	sf::Sprite sprite;

	

	sf::CircleShape shape;







};














#endif