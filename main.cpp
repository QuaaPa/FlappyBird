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
void eventUpdate(sf::RenderWindow* window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}
void DisplayPause(sf::Text* scoreText, sf::Text* bestScoreText)
{
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("resources/Pause.png");
    sf::Sprite pause(pauseTexture);
    pause.setPosition(WEIGHT / 2 - 70, HEIGHT / 2 - 176);

    // Draw text Score | Best Score
    scoreText->setPosition(WEIGHT / 2 - 70 + 53, HEIGHT / 2 - 176 + 47);
    scoreText->setFillColor(sf::Color::White);

    bestScoreText->setPosition(WEIGHT / 2 - 70 + 53, HEIGHT / 2 - 176 + 110);
    bestScoreText->setFillColor(sf::Color::White);

    window.draw(pause);
    window.draw(*scoreText);
    window.draw(*bestScoreText);
    window.display();
    while(isPause)
    {
        eventUpdate(&window);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            isPause = false;
        }
        else
        {
            isPause = true;
        }
    }
}

int main()
{
    srand(time(0));
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.loadFromFile("Arcade.ttf"))
    {
        return -1;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    int score = 0;

    sf::Text bestScoreText;
    bestScoreText.setFont(font);
    int bestScore = 0;

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
        //############ UPDATE EVENT ################
        eventUpdate(&window);
        //########## GET DELTA TIME  ###############
        dt = clockDt.getElapsedTime().asSeconds();
        clockDt.restart();
        //############# ANIMATION ##################
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
        //################ FALL DOWN #####################
        if (clockFall.getElapsedTime().asSeconds() > 0.3f)
        {
            if (rotate_bird < 30)
                rotate_bird += 10;
            bird.setRotation(rotate_bird);
            isJump = false;
        }
        //############## GENERATE TOWER ###################
        if (clockTower.getElapsedTime().asSeconds() >= 10.0f)
        {
            int random_y = rand() % 400;
            towers.push_back(Tower(tower, random_y));
            clockTower.restart();
        }
        //####### CHECK FOR CROSSING WITH FLOORR ###########
        if (bird.getPosition().y >= 730)
        {
            isPause = true;
        }
        else
        {
            isPause = false;
        }
        //################ CLEAR FRAME #####################
        window.clear();
        //################ DRAW FRAME ######################
        window.draw(background);
        if(towers.size() >= 1)
        {
            for (auto it = towers.begin(); it != towers.end(); it++)
            {
                it->update(dt);

                if(it->isIntersect(&bird))
                {
                    isPause = true;
                }
                if(it->isCrossing == false && it->getPositionX() < bird.getPosition().x)
                {
                    score += 1;
                    it->isCrossing = true;
                }

                if (it->getPositionX() < -100.0f)
                {
                    it = towers.erase(it);
                    clockTower.restart();
                }
                it->render(&window);

            }
        }
        window.draw(bird);
        //############## DISPLAY FRAME #####################
        if(isPause)
        {
            if(score >= bestScore)
            {
                bestScore = score;
            }
            scoreText.setString(std::to_string(score));
            bestScoreText.setString(std::to_string(bestScore));
            DisplayPause(&scoreText, &bestScoreText);
            towers.clear();
            score = 0;
            bird.setPosition(50, 350);
            clockTower.restart();
        }
        else
        {
            window.display();
        }
    }

    return 0;
}