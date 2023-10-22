#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>

class Tower
{
private:
    sf::Sprite TopTower;
    sf::Sprite BottomTower;
    sf::Vector2f BottomTowerPosition;

    sf::FloatRect TopTowerBounds;
    sf::FloatRect BottomTowerBounds;

    int towerSpacing = 350;

    float towerSpeed = 40.0f;

public:
    sf::Vector2f TopTowerPosition;
    bool isCrossing = false;
    Tower(sf::Sprite sprite, int position_y);

    float getPositionX();
    bool isIntersect(sf::Sprite* sprite);
    bool isGetScore(sf::Sprite* sprite);
    void update(float dt);
    void render(sf::RenderWindow* window);
};

#endif