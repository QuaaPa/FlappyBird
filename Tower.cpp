#include "Tower.hpp"

Tower::Tower(sf::Sprite sprite, int random_y)
{
    //#########  Set Sprite  #########
    TopTower = sprite;
    TopTower.setScale(1,-1);

    BottomTower = sprite;
    //#########  Set Position  #########
    TopTowerPosition.x = 686;
    TopTowerPosition.y = random_y - towerSpacing;

    BottomTowerPosition.x = 686;
    BottomTowerPosition.y = random_y + towerSpacing;
    //##########  Set Origin  ##########
    TopTower.setOrigin(43, 500);

    BottomTower.setOrigin(43, 0);
    //############  Set All  ############
    TopTower.setPosition(TopTowerPosition);
    // TopTower.setRotation(45);

    BottomTower.setPosition(BottomTowerPosition);
}

float Tower::getPositionX()
{
    return TopTower.getPosition().x;
}

bool Tower::isIntersect(sf::Sprite* sprite)
{
    if(sprite->getGlobalBounds().intersects(BottomTower.getGlobalBounds()) || sprite->getGlobalBounds().intersects(TopTower.getGlobalBounds()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tower::isGetScore(sf::Sprite *sprite)
{
    if(sprite->getPosition().x > getPositionX())
    {
        isCrossing = true;
        return true;
    }
    else
    {
        return false;
    }
}

void Tower::update(float dt)
{
    TopTower.move(-towerSpeed * dt, 0);
    BottomTower.move(-towerSpeed * dt, 0);
}

void Tower::render(sf::RenderWindow* window)
{
    window->draw(TopTower);
    window->draw(BottomTower);
}