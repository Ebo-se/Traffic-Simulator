//
// Created by Ebose on 2025-07-23.
//

#ifndef VEHICLE_H
#define VEHICLE_H

#include "SFML/Graphics.hpp"
#include "collider.cpp"

#include "trafficlight.h"

class vehicle {
private:
    int wait_time;
    bool isRunning = true; // Flag to control the vehicle's movement
    int direction; //1=N,-1=E
    sf::Vector2f startpos;
    static inline bool vehicleTextureLoaded = false;
    sf::Sprite vehicleSprite;
    static inline sf::Texture vehicleTexture{};
    collider Vehiclecollider{sf::Vector2f(42,42)}; // Collider for the vehicle, size can be adjusted
public:
    vehicle(int dir,sf::Vector2f startpos); //constructor
    void move(sf::Vector2f);
    int getdirection();
    static void loadTexture();
    void spawnVehicleNorth(sf::RenderWindow &window);
    sf::Vector2f getPosition() const { return vehicleSprite.getPosition(); }
    void collisionCheck(const collider &other, trafficlight &traffic);
    void stop() { isRunning = false; }
    void start() { isRunning = true;}
    void rotate();
};

#endif //VEHICLE_H
