//
// Created by Ebose on 2025-07-23.
//

#ifndef VEHICLE_H
#define VEHICLE_H
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class vehicle {
private:
    int wait_time;
    int direction; //1=N,-1=E
    double speed = 35.7;
    bool isRunning;
    sf::Vector2f startpos;
    static inline bool vehicleTextureLoaded = false;
    sf::Sprite vehicleSprite;
    static inline sf::Texture vehicleTexture{};
public:
    vehicle(int dir,sf::Vector2f startpos); //constructor
    int getdirection();
    static void loadTexture();
    void drawVehicle(sf::RenderWindow& window);
};

#endif //VEHICLE_H
