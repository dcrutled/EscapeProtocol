#include <string>
#include <vector>
#include <limits>
#include "CelestialObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Point.h"
#include "gameOver.h"
#include <SFML/Graphics.hpp>

using namespace std;



GameOver::GameOver(sf::Font f) {
	font = f;
	makeBackground();
}


void GameOver::draw(sf::RenderWindow& window) {


    window.draw(farStars);

    for (auto& star : middleStars) {

        float alpha = 177.5f + sin(star.twinkleTimer * star.twinkleSpeed) * 77.5f;
        star.shape.setFillColor({ 255, 255, 255, static_cast<uint8_t>(alpha) });
        window.draw(star.shape);
    }

    for (auto& star : nearStars) {

        float alpha = 177.5f + sin(star.twinkleTimer * star.twinkleSpeed) * 77.5f;
        star.shape.setFillColor({ 255, 255, 255, static_cast<uint8_t>(alpha) });
        window.draw(star.shape);
    }




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




    //sf::RectangleShape startButton;

    playAgain.setSize(sf::Vector2f(300, 150));
    playAgain.setOutlineColor(sf::Color::Red);
    playAgain.setOutlineThickness(2);
    playAgain.setOrigin({ 150,75 });
    playAgain.setPosition({ -50, -200 });
    playAgain.setFillColor(sf::Color(255, 0, 0, 0));

    window.draw(playAgain);



    sf::Text start(font);

    start.setCharacterSize(70);
    start.setFillColor(sf::Color::Yellow);

    start.setOutlineColor(sf::Color::Black);
    start.setOutlineThickness(1.f);

    start.setString("Play Again");

    float startX = -55;
    float startY = -215;




    start.setPosition(sf::Vector2f(startX, startY));


    sf::FloatRect startBounds = start.getGlobalBounds();

    start.setPosition({
        startX - startBounds.size.x / 2.f,
        startY - startBounds.size.y / 2.f - 2.f
        });

    //start.setStyle(sf::Text::Bold);

    //window.draw(text);
    window.draw(start);



    //sf::RectangleShape quitButton;

    quitButton.setSize(sf::Vector2f(300, 150));
    quitButton.setOutlineColor(sf::Color::Red);
    quitButton.setOutlineThickness(2);
    quitButton.setOrigin({ 150,75 });
    quitButton.setPosition({ -50, 0 });
    quitButton.setFillColor(sf::Color(255, 0, 0, 0));

    window.draw(quitButton);



    sf::Text quit(font);

    quit.setCharacterSize(70);
    quit.setFillColor(sf::Color::Yellow);

    quit.setOutlineColor(sf::Color::Black);
    quit.setOutlineThickness(1.f);

    quit.setString("Quit");

    float quitX = -55;
    float quitY = -10;




    quit.setPosition(sf::Vector2f(quitX, quitY));


    sf::FloatRect quitBounds = quit.getGlobalBounds();

    quit.setPosition({
        quitX - quitBounds.size.x / 2.f,
        quitY - quitBounds.size.y / 2.f - 2.f
        });


    window.draw(quit);



}


void GameOver::inputParse(sf::RenderWindow& window, sf::View& view, GameState& state) {
    while (const std::optional event = window.pollEvent())
    {


        if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
        {

            sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);


            if (playAgain.getGlobalBounds().contains(mouseWorld)) {
                state = GameState::StartScreen;
            }




            if (quitButton.getGlobalBounds().contains(mouseWorld)) {
                window.close();
            }


            
        }


        if (event->is<sf::Event::Closed>())
            window.close();
    }

}

void GameOver::update(float dt) {

    for (int i = 0; i < farStars.getVertexCount(); i++) {

        if (farStars[i].position.x >= (userScreen.size.x / 2.f)) {
            farStars[i].position.x = farStars[i].position.x - userScreen.size.x;
            farStars[i].position.y = farStars[i].position.y;
            continue;

        }

        farStars[i].position.x = farStars[i].position.x + .005;
        farStars[i].position.y = farStars[i].position.y;

    }


    for (auto& star : middleStars) {

        if (star.shape.getPosition().x >= (userScreen.size.x / 2.f)) {
            star.shape.setPosition({ (star.shape.getPosition().x - userScreen.size.x), star.shape.getPosition().y });

        }
        star.shape.setPosition({ star.shape.getPosition().x + .01f, star.shape.getPosition().y });
        star.twinkleTimer += dt;
    }

    for (auto& star : nearStars) {

        if (star.shape.getPosition().x >= (userScreen.size.x / 2.f)) {
            star.shape.setPosition({ (star.shape.getPosition().x - userScreen.size.x), star.shape.getPosition().y });

        }
        star.shape.setPosition({ star.shape.getPosition().x + .02f, star.shape.getPosition().y });

        star.twinkleTimer += dt;
    }


}

void GameOver::makeBackground() {
    farStars = sf::VertexArray(sf::PrimitiveType::Points);

    for (int i = 0; i < 800; i++) {

        sf::Vertex v;
        float x = (rand() % 6000) - 3000;
        float y = (rand() % 4500) - 2250;

        v.position = sf::Vector2f(x, y);

        farStars.append(v);

    }


    for (int i = 0; i < 300; i++) {

        Star star;



        star.shape.setRadius(1.0f);

        float x = (rand() % 6000) - 3000;
        float y = (rand() % 4500) - 2250;

        star.shape.setPosition({ x, y });

        middleStars.push_back(star);

    }


    for (int i = 0; i < 200; i++) {

        Star star;



        star.shape.setRadius(2.0f);

        float x = (rand() % 6000) - 3000;
        float y = (rand() % 4500) - 2250;

        star.shape.setPosition({ x, y });

        nearStars.push_back(star);

    }

}