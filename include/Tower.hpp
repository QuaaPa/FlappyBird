#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>

class Tower
{
private:
    sf::Sprite* firstTower;
    sf::Sprite* secondTower;
    sf::Vector2f firstPosition;
    sf::Vector2f secondPosition;

    float towerSpeed = 25;

public:
    Tower(sf::Sprite* sprite, int position_y);

    float getPosition();
    void update(float dt);
    void render(sf::RenderWindow* window);
};

#endif