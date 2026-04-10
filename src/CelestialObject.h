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

public:

	CelestialObject(float x, float y, float mass);
	//sf::CircleShape getShape(int i);

	void update();
	void draw();

private:

	float xcoord;
	float ycoord;
	float radius;
	float mass;
	float gravity;
	//sf::Sprite sprite;
	sf::CircleShape shape;







};














#endif