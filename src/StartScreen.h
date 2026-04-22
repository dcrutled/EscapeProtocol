#ifndef STARTSCREEN_H
#define STARTSCREEN_H

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




class StartScreen {


public:

	//update
	//inputParse
	//draw
	StartScreen(sf::Font);

	void loadAssets();

	void draw(sf::RenderWindow& window);
	void inputParse(sf::RenderWindow& window, sf::View&, GameState&);
	void update(float dt);

	void makeButtons();

	void makeBackground();


private:

	sf::VertexArray farStars;
	
	vector<Star> middleStars;
	vector<Star> nearStars;

	sf::Font font;

	sf::RectangleShape startButton;
	sf::RectangleShape quitButton;

	sf::VideoMode userScreen = sf::VideoMode::getDesktopMode();

	

};


#endif