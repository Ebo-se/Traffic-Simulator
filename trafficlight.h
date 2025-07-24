//
// Created by Ebose on 2025-07-23.
//

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
#include <mutex>
#include <SFML/Graphics.hpp>
class trafficlight {
private:
    int direction; //1 = N, -1 = E
    enum state {Red, Yellow, Green};
    state current;
    bool stopSignal;
    std::mutex mt;//to protect the code from crashing as we need to getstate and change colour at the same time
    sf::IntRect states[3]; //Different states of the traffic light and how they are drawn, 0 = red, 1 = yellow, 2 = green
    sf::Sprite sprite; //Sprite for the traffic light
    static inline sf::Texture texture{};
    static inline bool textureLoaded = false; //to check if the texture is loaded
public:
    trafficlight(int dir, int start_state); //start state is either red or green
    void changecolour();
    int getstate();
    void stop();
    void draw(sf::RenderWindow& window);
    void setposition(sf::Vector2f pos);
    static void loadTexture();
};

#endif //TRAFFICLIGHT_H
