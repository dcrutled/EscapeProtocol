#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include "CelestialObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Point.h"
#include "HUD.h"
#include <SFML/Graphics.hpp>

using namespace std;



HUD::HUD(sf::Font f) {

    font = f;

}













/*


void HUD::drawFuel(sf::RenderWindow& window) {

    int fuel = player->getFuel();




    sf::Text text(font);

    text.setCharacterSize(150);
    text.setFillColor(sf::Color::Yellow);

    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.f);

    text.setString("Game Over");

    float x = -50;
    float y = -400;




    text.setPosition(sf::Vector2f(x, y));


    sf::FloatRect bounds = text.getGlobalBounds();

    text.setPosition({
        x - bounds.size.x / 2.f,
        y - bounds.size.y / 2.f - 2.f
        });

    text.setStyle(sf::Text::Bold);

    //window.draw(text);
    window.draw(text);




}*/