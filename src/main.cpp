// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "GameState.h"
#include"StartScreen.h"
#include "LevelSelect.h"
#include "GameOver.h"
#include "GameSpace.h"


using namespace std;



int main()
{




    srand(time(0));

    


    GameSpace g;

    StartScreen start(g.getFont());  //initialize all of my game states 
    LevelSelect level(g.getFont());
    GameOver gg(g.getFont());

    float gameOverTimer = 0;
    
    GameState currentState = GameState::StartScreen;

    sf::VideoMode userScreen = sf::VideoMode::getDesktopMode();  //get size of users monitor

    sf::RenderWindow window(userScreen, "Solar System Escape");
    
    sf::Vector2f defaultZoom = { (float)userScreen.size.x, (float)userScreen.size.y };





    //-------------------------------------------------------------
    sf::View view(sf::FloatRect({ 0.f, 0.f }, { (float)userScreen.size.x, (float)userScreen.size.y })); //set origin at the center
    view.setCenter({ 0.f, 0.f });   // center your world at (0,0)

    window.setView(view);

    

    

    //-------------------------------------------------------------

    sf::Clock clock;                                                                                   //start clock for animation timers

    int idx = 0;
    float anim_timer = 0;
    float anim_speed = 0.23;

    while (window.isOpen())
    {

        float delta_time = clock.restart().asSeconds();                                               //change in time for animation timers
        sf::View defaultView = window.getView();                                                   // save after setting up initial view
        window.clear();

        switch (currentState) {

        case GameState::StartScreen:
            window.clear();
            start.inputParse(window, view,currentState);
            start.update(delta_time);
            start.draw(window);



            break;


        case GameState::LevelSelect:

            window.clear();
            level.inputParse(window, view, currentState);
            level.update(delta_time);
            level.draw(window);

            if (currentState == GameState::Playing) {
                g.initialize(level.level());
            }




            break;


        case GameState::Playing:


            g.inputParse(window, view);

            window.setView(view);

            window.clear();
            g.update(delta_time);
            g.draw(window);

            if (g.checkGameOver()) {
                gameOverTimer = gameOverTimer + delta_time;

                if (gameOverTimer >= 1) {
                    gameOverTimer = 0;
                    currentState = GameState::GameOver;
                }
            }


            break;


        case GameState::GameOver:
            window.clear();
            view.setSize(defaultZoom);
            view.setCenter({ 0.f, 0.f });
            window.setView(view);
            gg.inputParse(window, view, currentState);
            gg.update(delta_time);
            gg.draw(window);


            break;
        }





        window.display();
    }


}


















// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
