//
// Created by Ebose on 2025-07-23.
//

#include <iostream>
#include "trafficlight.h"
#include <chrono>
#include <thread>
//whenever we make the light we're gonna make a thread
const int red_stoptime = 50;// seconds
const int green_stoptime = 45;
const int yellow_stoptime = 5;
void trafficlight::loadTexture() {
    if (!textureLoaded) {
        if (!texture.loadFromFile("Graphic-elements/trafficlight.png")) {
            throw std::runtime_error("Failed to load texture from Graphics-elements/trafficlight.png");
        }
        textureLoaded = true;
    }
}

trafficlight::trafficlight(int dir, int start_state): direction(dir), stopSignal(false), sprite(texture){
    if (!textureLoaded) {
        throw std::logic_error("Texture not loaded. Call loadTexture() first!");
    }
    this->current = (start_state == 2) ? Yellow : Red;
    sprite.setOrigin({85.f, 385/2.f}); // Set origin to the center of the traffic light
    states[Red] = sf::IntRect({0, 66}, {170, 385});// Red light
    states[Yellow] = sf::IntRect({553/3,66},{170, 385}); // Yellow light
    states[Green] = sf::IntRect({553/3 + 170,66}, {170, 385}); // Green light
    sprite.setTextureRect(states[current]);
}
void trafficlight::changecolour() {
    while (!stopSignal) {
        {
            std::lock_guard<std::mutex> lock(mt);
            if (current == Red) {current = Green;}
            else if (current == Green) {current = Yellow;}
            else {current = Red;}
        }
        std::this_thread::sleep_for(
    current == Red ? std::chrono::seconds(red_stoptime) :
    current == Green ? std::chrono::seconds(green_stoptime) :
    std::chrono::seconds(yellow_stoptime)
);
    }
}
void trafficlight::draw(sf::RenderWindow &window) {
    sprite.setTextureRect(states[current]);
    window.draw(sprite);
}

int trafficlight::getstate() {
    std::lock_guard<std::mutex> lock(mt);
    switch (this->current) {
        case Red:return 0;
        case Green:return 2;
        case Yellow:return 1;
        default: return -1;
    }
}