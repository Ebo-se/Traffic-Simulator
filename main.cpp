#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "trafficlight.h"
#include "vehicle.h"
sf::Texture mapTextureLoader() //to load the texture of the ma[p
{
    sf::Texture map;
    if (!map.loadFromFile("Graphic-elements/map.png")) {
        throw std::runtime_error("Failed to load texture from Graphics-elements/map.png");
    }
    return map;
}
int main() {
    // Creating a window
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Traffic Light Test");
    window.setFramerateLimit(60); // Limit the frame rate to 60 FPS

    //Loading the map
    sf::Texture mapTexture;
    try {
        mapTexture = mapTextureLoader();
        trafficlight::loadTexture();
        vehicle::loadTexture();
    } catch (const std::exception& e) {
        std::cerr << "Failed to load texture: " << e.what() << std::endl;
        return 1;
    }
    //map
    sf::Sprite map_sprite(mapTexture);
    map_sprite.setPosition({0.f, 0.f});
    //trafficlight
    trafficlight NorthLight(1, 2); // North light starts red
    trafficlight EastLight(-1, 0); // East light starts green
    std::thread northLightThread(&trafficlight::changecolour, &NorthLight);
    std::thread eastLightThread(&trafficlight::changecolour, &EastLight);
    NorthLight.setposition({620.f, 600.f}); // Set position for North light
    NorthLight.setscale({0.17f, 0.17f}); // Set scale for North light
    EastLight.setposition({400.f, 400.f}); // Set position for East light
    EastLight.setscale({0.17f, 0.17f}); // Set scale for East light
    //vehicle
    vehicle car1(1, sf::Vector2f{548.55f, 895.f});


    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {window.close();}
        }

        window.clear();
        window.draw(map_sprite);
        NorthLight.draw(window); EastLight.draw(window);
        car1.drawVehicle(window);
        window.display();
    }
    // Clean up threads
    NorthLight.stop(); EastLight.stop();
    northLightThread.join(); eastLightThread.join();
    return 0;
}
