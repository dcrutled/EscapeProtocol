#ifndef HUD_H
#define HUD_H

#include <string>
#include <vector>
#include <limits>
#include "CelestialObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Point.h"
#include "Star.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>


class HUD {

public:

	HUD(sf::Font);
	//void drawFuel(sf::RenderWindow& window);






private:
	sf::Font font;



};


#endif