// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "GameSpace.h"


using namespace std;



int main()
{
/*
    vector<sf::Texture> planets;

    for (auto& entry : filesystem::directory_iterator("assets/Gas Giants/")) {

        sf::Texture planet_sheet;
        planet_sheet.loadFromFile(entry);
        planets.push_back(planet_sheet);
    }


    /*sf::Texture planet_sheet;


    if (!planet_sheet.loadFromFile("assets/Planets/blue_cloudy_water_planet.png")) {
        cout << "ERROR" << endl;
    }
    


    sf::Sprite planet(planets[2]);

    planet.setPosition({ 100.0f, 100.0f });

    
    planet.setTextureRect(sf::IntRect({0,0},{300,300}));

    */




    srand(time(0));
    string choice;
    int rings;
    bool entryCheck = true;

    do{
        

        cout << "Welcome to Solar System Escape" << endl
            << "Type \"yes\" to begin or \"quit\" to exit." << endl;

    

        cin >> choice;

        if (choice == "yes") {
            entryCheck = false;
        }

        else if (choice == "quit" ) {
            cout << "Thanks for playing!" << endl;
            return 0;
        }

        else if (choice != "yes" || choice != "quit") {
            cout << "Invalid Entry" << endl << endl;
        }
    
    } while (entryCheck);



    cout << "Please enter the number of rings for your game: ";
    cin >> rings;

    if (rings == 0) {
        cout << "Invalid number of rings.";
        return 0;
    }

    GameSpace g(rings);
    sf::VideoMode userScreen = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(userScreen, "Solar System Escape");
    
    //sf::RenderWindow window(sf::VideoMode({ 1920, 1400 }), "SFML works!");
   //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    // 
    // 
    // 
    //-------------------------------------------------------------
    sf::View view(sf::FloatRect({ 0.f, 0.f }, { (float)userScreen.size.x, (float)userScreen.size.y }));
    view.setCenter({ 0.f, 0.f });   // center your world at (0,0)

    window.setView(view);

    

    //-------------------------------------------------------------

    sf::Clock clock;

    int idx = 0;
    float anim_timer = 0;
    float anim_speed = 0.23;

    while (window.isOpen())
    {
        //std::cout << view.getSize().x << " " << view.getSize().y << std::endl;
        float delta_time = clock.restart().asSeconds();
        sf::View defaultView = window.getView(); // save this once after setting up your initial view
        float currentZoom = 1.0f;
        g.inputParse(window, view);

        /*

        while (const std::optional event = window.pollEvent())
        {

            //------------------------------------------------------------------------


            if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                // Convert mouse pixel position to world coordinates
                sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

                float zoomFactor = (scroll->delta > 0) ? 0.9f : 1.1f;

                if (view.getSize().x > 4000 && view.getSize().y > 2500) {
                    zoomFactor = (scroll->delta > 0) ? 0.9f : 1.0;
                }


                view.zoom(zoomFactor);

                // After zooming, shift the view center toward the mouse position
                sf::Vector2f newMouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
                view.move(mouseWorld - newMouseWorld);

                window.setView(view);
            }

    
            //------------------------------------------------------------------------


            if (event->is<sf::Event::Closed>())
                window.close();
        }




        

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            if (view.getCenter().y < -500.f) {
                view.move({ 0,0 });
                //window.setView(view);
            }
            else {
                view.move({ 0, -2.f });
                //window.setView(view);
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            if (view.getCenter().y > 500.f) {
                view.move({ 0,0 });
                //window.setView(view);
            }
            else {
                view.move({ 0, 2.f });
                //window.setView(view);
            }


        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            if (view.getCenter().x < -500.f) {
                view.move({ 0,0 });
                //window.setView(view);
            }
            else {
                view.move({ -2.f, 0 });
                //window.setView(view);
            }


        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            if (view.getCenter().x > 500.f) {
                view.move({ 0,0 });
                //window.setView(view);
            }
            else {
                view.move({ 2.f, 0 });
                //window.setView(view);
            }
        }

        */
        
        window.setView(view);

        window.clear();
        g.update(delta_time);
        g.draw(window);
        //window.draw(planet);
        //window.draw(shape);
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
