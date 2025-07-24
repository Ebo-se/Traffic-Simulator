//
// Created by Ebose on 2025-07-23.
//

#include <iostream>
#include "trafficlight.h"
#include <chrono>
#include <thread>
#include <filesystem>
namespace fs = std::filesystem;
//whenever we make the light we're gonna make a thread
const int red_stoptime = 10;
const int green_stoptime = 6;
const int yellow_stoptime = 2;
void trafficlight::loadTexture() {
    if (!textureLoaded) {
        fs::path texturePath = fs::current_path() / "Traffic-Simulator" / "Graphics-elements" / "trafficlight.png";

        if (!texture.loadFromFile(texturePath.string())) {
            throw std::runtime_error("Error loading texture from file: " + texturePath.string());
        }
        textureLoaded = true;
    }
}

trafficlight::trafficlight(int dir, int start_state): direction(dir), stopSignal(false), sprite(texture){
    if (!textureLoaded) {
        throw std::logic_error("Texture not loaded. Call loadTexture() first!");
    }
    this->current = (start_state == 2) ? Green : Red;
    sprite.setOrigin({140, 275}); // Set origin to the center of the traffic light
    for (int i = 0; i < 3; i++) {
        states[i] = sf::IntRect({{275 * i,100}, {280,550}});
    }
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

void trafficlight::stop() {this->stopSignal = true;}
int trafficlight::getstate() {
    std::lock_guard<std::mutex> lock(mt);
    switch (this->current) {
        case Red:return 0;
        case Green:return 2;
        case Yellow:return 1;
        default: return -1;
    }
}