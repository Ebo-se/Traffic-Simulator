//
// Created by Ebose on 2025-07-23.
//

#include "vehicle.h"
#include "SFML/Graphics.hpp"
#include "trafficlight.h"
#include <iostream>

void vehicle:: loadTexture()
{
    if (!vehicleTextureLoaded)
    {
        if (!vehicleTexture.loadFromFile("Graphic-elements/vehicle.png"))
        {
            throw std::runtime_error("Failed to load texture from Graphics-elements/vehicle.png");
        }
        vehicleTextureLoaded = true;
    }
}
vehicle::vehicle(int dir, sf::Vector2f startpos): vehicleSprite(vehicleTexture)
{
    if (!vehicleTextureLoaded)
    {
        throw std::logic_error("Texture not loaded. Call loadTexture() first!");
    }
    this->direction = dir;
    vehicleSprite.setPosition(startpos);
    vehicleSprite.setScale(sf::Vector2f(0.04f, 0.04f));
    Vehiclecollider.setPosition(startpos);
}
void vehicle::move(sf::Vector2f destination) {
    if (isRunning) {
        vehicleSprite.move(destination);
        Vehiclecollider.setPosition(vehicleSprite.getPosition());
    }
}


int vehicle::getdirection() {return direction;}


void vehicle::spawnVehicleNorth(sf::RenderWindow &window)
{
    window.draw(vehicleSprite);
}

void vehicle::collisionCheck(const collider &other, trafficlight &traffic) {
    if (Vehiclecollider.intersects(other)) {
        if (traffic.getstate() == 0) {stop();}
        else {start();}
    }
}

void vehicle::rotate() {
    if (direction == 1) {
        vehicleSprite.setRotation(sf::degrees(0.f)); // North
    } else if (direction == -1) {
        vehicleSprite.setRotation(sf::degrees(90.f)); // East
    }
}