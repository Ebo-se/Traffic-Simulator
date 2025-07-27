//
// Created by Ebose on 2025-07-23.
//

#include "vehicle.h"

#include "SFML/Graphics/Texture.hpp"

vehicle::vehicle(int dir) {this->direction = dir;}


int vehicle::getdirection() {return direction;}

void vehicle:: loadTexture()
{
    sf::Texture vehicleTexture;
    if (!vehicleTextureLoaded)
    {
        if (!vehicleTexture.loadFromFile(".Graphic-elements/vehicle.png"))
        {
            throw std::runtime_error("Failed to load texture from Graphics-elements/vehicle.png");
        }
        vehicleTextureLoaded = true;
    }
}

