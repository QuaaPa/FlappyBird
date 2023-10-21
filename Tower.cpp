#include "Tower.hpp"

Tower::Tower(sf::Sprite* sprite, int position_y)
    : firstTower(sprite),
      secondTower(sprite) //! will be flipped a texture horizontally
{
    firstPosition.x = 600 + 86;                // | First Tower
    firstPosition.y = position_y;              // | Position
    firstTower->setOrigin(86, 0);

    secondPosition.x = firstPosition.x;        // | Second Tower
    secondPosition.y = firstPosition.y - 100;  // | Position
    secondTower->setScale(1, -1);              // | flipping a texture horizontally
    secondTower->setOrigin(86, 967);           // | flipping a texture horizontally
}

float Tower::getPosition()
{
    return firstPosition.x;
}

void Tower::update(float dt)
{
    firstTower->move(-10 * dt * towerSpeed, 0);
    secondTower->move(-10 * dt * towerSpeed, 0);
}

void Tower::render(sf::RenderWindow* window)
{
    window->draw(*firstTower);
    window->draw(*secondTower);
}