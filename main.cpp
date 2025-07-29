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
    collider northline({140.f,20.f});
    northline.setPosition({437.5f, 585.f});
    collider eastline({20.f,150.f});
    eastline.setPosition({445.f, 420.f});
    //speed
    float redLightspeed = 0.1f;
    float greenLightspeed = 0.125f;
    float yellowLightspeed = 0.13f;

    //startpos north
    sf::Vector2f northLane1 {548.55f, 1000.f};
    sf::Vector2f eastlane1 {0, 422.5f};

    // movement vectors
    sf::Vector2f northToSouthLane1({0.f,-895.f});
    sf::Vector2f eastToSouthLane1({900.f,0.f});

    // vehicle
    vehicle car(1, northLane1);
    vehicle car1(-1, eastlane1);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time timeElapsed = clock.restart();
        int northernLight_state = NorthLight.getstate();
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {window.close();}
        }

        window.clear();
        window.draw(map_sprite);
        NorthLight.draw(window); EastLight.draw(window);

        car.spawnVehicleNorth(window);
        car1.rotate();
        car1.spawnVehicleNorth(window);
        car.move(northToSouthLane1*timeElapsed.asSeconds()*0.1f);
        car.move(eastlane1*timeElapsed.asSeconds()*0.1f);
        if (northernLight_state == 0) {car.move(northToSouthLane1*redLightspeed*timeElapsed.asSeconds());}
        else if (northernLight_state == 2){car.move(northToSouthLane1*timeElapsed.asSeconds()*greenLightspeed);}
        else if (northernLight_state == 1){car.move(northToSouthLane1*timeElapsed.asSeconds()*yellowLightspeed);}
        if (EastLight.getstate() == 0) {car1.move(eastToSouthLane1*redLightspeed*timeElapsed.asSeconds());}
        else if (EastLight.getstate() == 2){car1.move(eastToSouthLane1*timeElapsed.asSeconds()*greenLightspeed);}
        else if (EastLight.getstate() == 1){car1.move(eastToSouthLane1*timeElapsed.asSeconds()*yellowLightspeed);}
        car.collisionCheck(northline,NorthLight); // Check for collisions with the line collider
        car1.collisionCheck(eastline,EastLight);
        window.display();

    }
    // Clean up threads
    NorthLight.stop(); EastLight.stop();
    northLightThread.join(); eastLightThread.join();
    return 0;
}
