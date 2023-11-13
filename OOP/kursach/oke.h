#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <time.h>

struct node {
    float x, y;
};

/*class node {
protected:
    float x, y;
    node()
    {
        this->x = rand() % 1000;
        this->y = rand() % 750;
    }
};
*/

class snake {
private:
    node count[10];
    float volume;
    int size;

    void check(int i)
    {
        if (count[i].x >= 1000) {
            count[i].x = 0;
        }
        if (count[i].x < 0) {
            count[i].x = 1000 - volume;
        }
        if (count[i].y >= 750) {
            count[i].y = 0;
        }
        if (count[i].y < 0) {
            count[i].y = 750 - volume;
        }
    }

public:
    snake()
    {
        this->size = 4;
        count[0].x = 750;
        count[0].y = 375;
        this->volume = 50;
        for (int i = 1; i < size; ++i) {
            count[i].x = count[i - 1].x - volume;
            count[i].y = count[i - 1].y;
        }
    }

    void movement(int expression)
    {
        switch (expression) {
        case (1):
            for (int i = size - 1; i > 0; --i) {
                count[i].x = count[i - 1].x;
                count[i].y = count[i - 1].y;
                check(i);
            }
            count[0].x += volume;
            check(0);
            break;
        case (2):
            for (int i = size - 1; i > 0; --i) {
                count[i].x = count[i - 1].x;
                count[i].y = count[i - 1].y;
                check(i);
            }
            count[0].x -= volume;
            check(0);
            break;
        case (3):
            for (int i = size - 1; i > 0; --i) {
                count[i].y = count[i - 1].y;
                count[i].x = count[i - 1].x;
                check(i);
            }
            count[0].y += volume;
            check(0);
            break;
        case (4):
            for (int i = size - 1; i > 0; --i) {
                count[i].y = count[i - 1].y;
                count[i].x = count[i - 1].x;
                check(i);
            }
            count[0].y -= volume;
            check(0);
            break;
        default:
            break;
        }
    }

    void setX(float _x)
    {
        count[0].x = _x;
    }

    void setY(float _y)
    {
        count[0].y = _y;
    }

    void setVolume(float volume)
    {
        this->volume = volume;
    }

    int getSize()
    {
        return size;
    }

    float getVolume()
    {
        return volume;
    }

    float getX(int i)
    {
        return count[i].x;
    }

    float getY(int i)
    {
        return count[i].y;
    }
};

class menu {
private:
    sf::Text play;
    sf::Text settings;
    sf::Text exit;
    sf::Font font;
    char color[3] = {'g', 'r', 'r'};

public:
    menu()
    {
        play.setFont(font);
        play.setString("Play");
        play.setCharacterSize(100);
        play.setFillColor(sf::Color::Green);
        play.setPosition(400, 100);

        settings.setFont(font);
        settings.setString("Settings");
        settings.setCharacterSize(100);
        settings.setFillColor(sf::Color::Red);
        settings.setPosition(400, 200);

        exit.setFont(font);
        exit.setString("Exit");
        exit.setCharacterSize(100);
        exit.setFillColor(sf::Color::Red);
        exit.setPosition(400, 300);

        if (!font.loadFromFile("ArialBlack.ttf")) {
            throw "No font";
        }
    }

    char getColor(int i)
    {
        return color[i];
    }

    sf::Text getPlay()
    {
        return play;
    }

    sf::Text getSettings()
    {
        return settings;
    }

    sf::Text getExit()
    {
        return exit;
    }

    void Down()
    {
        for (int i = 0; i < 3; ++i) {
            if (color[i] == 'g') {
                switch (i) {
                case 0:
                    play.setFillColor(sf::Color::Red);
                    settings.setFillColor(sf::Color::Green);
                    color[i] = 'r';
                    color[i + 1] = 'g';
                    break;
                case 1:
                    settings.setFillColor(sf::Color::Red);
                    exit.setFillColor(sf::Color::Green);
                    color[i] = 'r';
                    color[i + 1] = 'g';
                    break;
                case 2:
                    exit.setFillColor(sf::Color::Red);
                    play.setFillColor(sf::Color::Green);
                    color[i] = 'r';
                    color[0] = 'g';
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }

    void Up()
    {
        for (int i = 0; i < 3; ++i) {
            if (color[i] == 'g') {
                switch (i) {
                case 0:
                    play.setFillColor(sf::Color::Red);
                    exit.setFillColor(sf::Color::Green);
                    color[i] = 'r';
                    color[2] = 'g';
                    break;
                case 1:
                    settings.setFillColor(sf::Color::Red);
                    play.setFillColor(sf::Color::Green);
                    color[i] = 'r';
                    color[i - 1] = 'g';
                    break;
                case 2:
                    exit.setFillColor(sf::Color::Red);
                    settings.setFillColor(sf::Color::Green);
                    color[i] = 'r';
                    color[i - 1] = 'g';
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }

    void Default()
    {
        play.setFillColor(sf::Color::Green);
        settings.setFillColor(sf::Color::Red);
        exit.setFillColor(sf::Color::Red);
        color[0] = 'g';
        color[1] = 'r';
        color[2] = 'r';
    }

    void Enter()
    {
    }
};