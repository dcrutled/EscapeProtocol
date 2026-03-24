// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "GameSpace.h"


using namespace std;



int main()
{




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


    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");
   //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    //-------------------------------------------------------------
    sf::View view(sf::FloatRect({ 0.f, 0.f }, { 1920.f, 1080.f }));
    view.setCenter({ 0.f, 0.f });   // center your world at (0,0)

    window.setView(view);

    //-------------------------------------------------------------

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {

            //------------------------------------------------------------------------


            if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                

                if (scroll->delta > 0)
                    view.zoom(0.9f);
                else
                    view.zoom(1.1f);

                window.setView(view);
            }

            //------------------------------------------------------------------------


            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        g.draw(window);
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
