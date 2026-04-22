#include <string>
#include <vector>
#include <limits>
#include "CelestialObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Point.h"
#include "LevelSelect.h"
#include <SFML/Graphics.hpp>

using namespace std;





LevelSelect::LevelSelect(sf::Font f) {
    //loadAssets();
    font = f;
    makeBackground();
    makeButtons();
}

void LevelSelect::makeButtons() {
    levelButtons = {};


    float buttonX = -500;
    float buttonY = -200;

    for (int i = 0; i < 10; i++) {

        sf::RectangleShape temp;

        temp.setSize(sf::Vector2f(200, 100));
        temp.setOutlineColor(colors[i]);
        temp.setOutlineThickness(2);
        temp.setOrigin({ 100,50 });
        temp.setPosition({ buttonX, buttonY });
        temp.setFillColor(sf::Color(255, 0, 0, 0));
    
        
        buttonX = buttonX + 250;

        if (i == 4) {
            buttonX = -500;
            buttonY = 50;
        }

        levelButtons.push_back(temp);

        


    }

}



void LevelSelect::draw(sf::RenderWindow& window) {


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

    float buttonX = -500;
    float buttonY = -200;


    for (int i = 0; i < 10; i++) {

        window.draw(levelButtons[i]);


  
        sf::Text level(font);

        level.setCharacterSize(70);
        level.setFillColor(sf::Color::White);

        level.setOutlineColor(sf::Color::Black);
        level.setOutlineThickness(1.f);
        

        level.setString(to_string(i + 1) + " Rings");

        if(i==0){ level.setString(to_string(i + 1) + " Ring"); }

        float levelX = buttonX;
        float levelY = buttonY - 10;




        level.setPosition(sf::Vector2f(levelX, levelY));


        sf::FloatRect levelBounds = level.getGlobalBounds();

        level.setPosition({
            levelX - levelBounds.size.x / 2.f,
            levelY - levelBounds.size.y / 2.f - 2.f
            });


        window.draw(level);

        buttonX = buttonX + 250;

        if (i == 4) {
            buttonX = -500;
            buttonY = 50;
        }



    }




}



void LevelSelect::inputParse(sf::RenderWindow& window, sf::View& view, GameState& state) {

    while (const std::optional event = window.pollEvent())
    {

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

        //--------------------------------------------------------------------


        if (levelButtons[0].getGlobalBounds().contains(mousePos)) {
            levelButtons[0].setOutlineThickness(6);

        }
        else if (!levelButtons[0].getGlobalBounds().contains(mousePos)) {
            levelButtons[0].setOutlineThickness(2);

        }

        //---------------------------------------------------------------------

        if (levelButtons[1].getGlobalBounds().contains(mousePos)) {
            levelButtons[1].setOutlineThickness(6);

        }
        else if (!levelButtons[1].getGlobalBounds().contains(mousePos)) {
            levelButtons[1].setOutlineThickness(2);

        }

        //---------------------------------------------------------------------

        if (levelButtons[2].getGlobalBounds().contains(mousePos)) {
            levelButtons[2].setOutlineThickness(6);

        }
        else if (!levelButtons[2].getGlobalBounds().contains(mousePos)) {
            levelButtons[2].setOutlineThickness(2);

        }

        //--------------------------------------------------------------------

        if (levelButtons[3].getGlobalBounds().contains(mousePos)) {
            levelButtons[3].setOutlineThickness(6);

        }
        else if (!levelButtons[3].getGlobalBounds().contains(mousePos)) {
            levelButtons[3].setOutlineThickness(2);

        }

        //--------------------------------------------------------------------

        if (levelButtons[4].getGlobalBounds().contains(mousePos)) {
            levelButtons[4].setOutlineThickness(6);

        }
        else if (!levelButtons[4].getGlobalBounds().contains(mousePos)) {
            levelButtons[4].setOutlineThickness(2);

        }

        //--------------------------------------------------------------------

        if (levelButtons[5].getGlobalBounds().contains(mousePos)) {
            levelButtons[5].setOutlineThickness(6);

        }
        else if (!levelButtons[5].getGlobalBounds().contains(mousePos)) {
            levelButtons[5].setOutlineThickness(2);

        }

        //--------------------------------------------------------------------

        if (levelButtons[6].getGlobalBounds().contains(mousePos)) {
            levelButtons[6].setOutlineThickness(6);

        }
        else if (!levelButtons[6].getGlobalBounds().contains(mousePos)) {
            levelButtons[6].setOutlineThickness(2);

        }

        //--------------------------------------------------------------------

        if (levelButtons[7].getGlobalBounds().contains(mousePos)) {
            levelButtons[7].setOutlineThickness(6);

        }
        else if (!levelButtons[7].getGlobalBounds().contains(mousePos)) {
            levelButtons[7].setOutlineThickness(2);

        }

        //--------------------------------------------------------------------

        if (levelButtons[8].getGlobalBounds().contains(mousePos)) {
            levelButtons[8].setOutlineThickness(6);

        }
        else if (!levelButtons[8].getGlobalBounds().contains(mousePos)) {
            levelButtons[8].setOutlineThickness(2);

        }

        //--------------------------------------------------------------------

        if (levelButtons[9].getGlobalBounds().contains(mousePos)) {
            levelButtons[9].setOutlineThickness(6);

        }
        else if (!levelButtons[9].getGlobalBounds().contains(mousePos)) {
            levelButtons[9].setOutlineThickness(2);

        }

        //--------------------------------------------------------------------

        if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
        {

            sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);  //chooses ring count based on button selection


            if (levelButtons[0].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 1;
                
                state = GameState::Playing;
            }

            else if (levelButtons[1].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 2;
                state = GameState::Playing;
                
            }

            else if (levelButtons[2].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 3;
                state = GameState::Playing;
            }

            else if (levelButtons[3].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 4;
                state = GameState::Playing;
            }

            else if (levelButtons[4].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 5;
                state = GameState::Playing;
            }

            else if (levelButtons[5].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 6;
                state = GameState::Playing;
            }

            else if (levelButtons[6].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 7;
                state = GameState::Playing;
            }

            else if (levelButtons[7].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 8;
                state = GameState::Playing;
            }

            else if (levelButtons[8].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 9;
                state = GameState::Playing;
            }

            else if (levelButtons[9].getGlobalBounds().contains(mouseWorld)) {
                levelNum = 10;
                state = GameState::Playing;
            }

        }







        if (event->is<sf::Event::Closed>())
            window.close();
    }



}



void LevelSelect::update(float dt) {

    for (int i = 0; i < farStars.getVertexCount(); i++) {                    //update will change the location of each star for parallax motion

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


void LevelSelect::makeBackground() {

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

int LevelSelect::level() {
    return levelNum;
}