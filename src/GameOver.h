#ifndef GAMEOVER_H
#define GAMEOVER_H

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




class GameOver {


public:

	
	GameOver(sf::Font);

	

	void draw(sf::RenderWindow& window);
	void inputParse(sf::RenderWindow& window, sf::View&, GameState&);

	void update(float dt);

	void makeBackground();

	void makeButtons();

	


private:

	sf::VertexArray farStars;

	vector<Star> middleStars;
	vector<Star> nearStars;

	sf::Font font;

	sf::RectangleShape playAgain;
	sf::RectangleShape quitButton;


	sf::VideoMode userScreen = sf::VideoMode::getDesktopMode();

	

};


#endif