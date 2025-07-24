#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "trafficlight.h"
int main() {
    try {
        // Load the traffic light texture (MUST BE DONE BEFORE constructing any trafficlight)
        trafficlight::loadTexture();
    } catch (const std::exception& e) {
        std::cerr << "Failed to load texture: " << e.what() << std::endl;
        return 1;
    }

    // Create a window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Traffic Light Test");
    window.setFramerateLimit(60); // Limit the frame rate to 60 FPS

    // Northbound red starting traffic light
    trafficlight light(1, 0);

    // Start the traffic light's state change in a separate thread
    std::thread lightThread(&trafficlight::changecolour, &light);

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {window.close();}
        }

        window.clear();
        light.draw(window);
        window.display();
    }

    // Stop the light when the window closes
    light.stop();
    lightThread.join(); // Wait for thread to exit safely
    return 0;
}