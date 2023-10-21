#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <sstream>
#include <vector>

#include "Tower.hpp"

const int WEIGHT = 600;
const int HEIGHT = 900;

sf::RenderWindow window(sf::VideoMode(WEIGHT, HEIGHT), "Flappy Bird");

bool isPause = false;

void Pause()
{
    isPause = true;
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("resources/Pause.png");
    sf::Sprite pause(pauseTexture);
    pause.setPosition(WEIGHT / 2 - 70, HEIGHT / 2 - 176);

    // Draw text Score | Best Score

    window.draw(pause);
}

bool CheckGameOver(sf::Sprite bird)
{
    if (bird.getPosition().y >= 730)
    {
        Pause();
        return true;
    }
    else
        return false;
}

int main()
{
    srand(time(0));
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("resources/background.png"))
    {
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    sf::Texture birdTexture;
    if (!birdTexture.loadFromFile("resources/Sprite.png"))
    {
        return -1;
    }

    sf::Texture towerTexture;
    if (!towerTexture.loadFromFile("resources/Tower.png"))
    {
        return -1;
    }
    sf::Sprite tower(towerTexture);
    // tower.setPosition(0, 416);
    tower.setScale(0.5, 0.5);

    std::vector<Tower> towers;

    float boostfall = 1.5f;
    float velocityUP = 1.5f;

    float vy_bird = 0;
    float rotate_bird = 0;

    sf::IntRect rectSourceSprite(0, 0, 64, 64);
    sf::Sprite bird(birdTexture, rectSourceSprite);
    bird.setPosition(50, 350);
    bird.setOrigin(32, 32);

    sf::Clock clockTower;
    sf::Clock clockFall;
    sf::Clock clock;
    sf::Clock clockDt;
    float dt = 0;

    bool isJump = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dt = clockDt.getElapsedTime().asSeconds();
        clockDt.restart();

        if (clock.getElapsedTime().asSeconds() > 0.1f)
        {
            if (rectSourceSprite.left >= 128)
                rectSourceSprite.left = 0;
            else
                rectSourceSprite.left += 64;

            bird.setTextureRect(rectSourceSprite);
            clock.restart();
        }

        //############# DEFAULT MOVE ##################
        if (!isJump)
            if (vy_bird != 360)
                vy_bird += 60;
        bird.move(0, vy_bird * boostfall * dt);
        //############## SPACE MOVE ###################
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            vy_bird = 0;
            rotate_bird = 0;
            if (vy_bird != -360)
                vy_bird -= 120;
            if (rotate_bird > -30)
                rotate_bird -= 10;
            bird.setRotation(rotate_bird);
            bird.move(0, vy_bird * velocityUP * dt);

            isJump = true;
            clockFall.restart();
        }

        if (clockFall.getElapsedTime().asSeconds() > 0.3f)
        {
            if (rotate_bird < 30)
                rotate_bird += 10;
            bird.setRotation(rotate_bird);
            isJump = false;
        }
        window.setTitle(std::to_string(clockTower.getElapsedTime().asSeconds()));
        if (clockTower.getElapsedTime().asSeconds() >= 4.0f)
        {
            int random_y = rand() % 201 + 500;
            towers.push_back(Tower(&tower, random_y));
            clockTower.restart();
        }
        window.clear();
        if(!towers.empty())
        {
            for (auto it = towers.begin(); it != towers.end();)
            {
                it->update(dt);

                if (it->getPosition() < -100.0f)
                {
                    it = towers.erase(it);
                    clockTower.restart();
                }
                it->render(&window);
            }
        }
        window.draw(background);
        window.draw(bird);
        if (CheckGameOver(bird))
        {
            window.display();
            while (isPause)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    isPause = false;
                    bird.setPosition(50, 350);
                }
                else
                {
                    isPause = true;
                }
            }
        }
        else
            window.display();
    }

    return 0;
}