//
// Created by engin on 2025-08-16.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "vehicle.h"

class spawner
{   private:
    //starting vectors
    const sf::Vector2f northLane1 {548.55f, 1000.f};
    const sf::Vector2f northLane2 {511.55f, 1000.f};
    const sf::Vector2f northLane3{473.55f, 1000.f};
    const sf::Vector2f northLane4{432.75f, 1000.f};
    const sf::Vector2f eastLane1 {0, 527.95f};
    const sf::Vector2f eastLane2{0, 492.95f};
    const sf::Vector2f eastLane3{0, 457.f};
    const sf::Vector2f eastLane4{0, 422.5f};

    //movement vectors
    sf::Vector2f northToSouthLane1 {0.f,-895.f};


    public:
    void spawnerNORTH(sf::RenderWindow &window)
    {
        sf::Vector2f northLane;
        srand(time(NULL));
        int lanenumber = rand() % 4 + 1;
        switch (lanenumber)
        {
            case 1: northLane =northLane1; break;
            case 2: northLane =northLane2; break;
            case 3: northLane =northLane3; break;
            case 4: northLane =northLane4; break;
        }
        vehicle northernCar(1,northLane1);
        northernCar.spawnVehicleNorth(window);
        northernCar.move(northToSouthLane1);



    }
    void spawnerEAST()
    {
        vehicle easternCar(-1,eastLane1);
    }


};
