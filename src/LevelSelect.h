#ifndef LEVELSELECT_H
#define LEVELSELECT_H

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




class LevelSelect {     //class for the level select window


public:

	
	LevelSelect(sf::Font);     //grab our font that was loaded in gamespace constructor

	

	void draw(sf::RenderWindow& window);
	void inputParse(sf::RenderWindow& window, sf::View&, GameState&);
	void update(float dt);

	void makeBackground();

	void makeButtons();

	int level();


private:

	sf::VertexArray farStars;

	vector<Star> middleStars;
	vector<Star> nearStars;

	sf::Font font;

	vector<sf::RectangleShape> levelButtons;

	vector<sf::Color> colors = {
	sf::Color::Red,
	sf::Color::Green,
	sf::Color::Blue,
	sf::Color::Yellow,
	sf::Color::Cyan,
	sf::Color::Magenta,
	sf::Color::White,
	sf::Color(255, 128, 0),   // orange
	sf::Color(128, 0, 255),   // purple
	sf::Color(0, 255, 128)    // mint
	};

	int levelNum;

	sf::VideoMode userScreen = sf::VideoMode::getDesktopMode();
};


#endif