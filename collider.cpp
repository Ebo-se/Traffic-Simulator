//
// Created by Ebose on 2025-07-29.
//

#include <SFML/Graphics.hpp>

class collider {
private:
    sf::RectangleShape rect;
public:
    collider(sf::Vector2f size) {
        rect.setSize(size);
        rect.setFillColor(sf::Color::Transparent); // Make it invisible
        rect.setOutlineThickness(1.f);
        rect.setOutlineColor(sf::Color::Blue); // Optional: outline for visibility
    }

    const sf::RectangleShape& getRectangle() const {return rect;}

    void setPosition(sf::Vector2f position) {rect.setPosition(position);}

    bool intersects(const collider& other) const {
        if (rect.getGlobalBounds().findIntersection(other.getRectangle().getGlobalBounds())) {return true;}
        return false;
    }

    void setsize(sf::Vector2f size) {rect.setSize(size);}
    void draw(sf::RenderWindow &window) {window.draw(rect);}
};
