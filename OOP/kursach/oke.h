#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>

struct node {
    float x, y;
};

class entity : sf::Drawable {
protected:
    int size;

public:
    virtual void movement() = 0;
};

class apple : public entity {
private:
    node position;

public:
    
};

class snake : public entity {
private:
    node count[10];
    float volume;
    sf::CircleShape head;
    sf::RectangleShape rectangle[9];

    void transition(int i)
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

    bool check(int temp, int expression)
    {
        switch (expression) {
        case 1:
        case 2:
            for (int i = 0; i < size; ++i) {
                if ((temp == count[i].x || temp >= 1000 && 0 == count[i].x
                     || temp < 0 && (1000 - volume) == count[i].x)
                    && count[0].y == count[i].y) {
                    return true;
                }
            }
            return false;
            break;
        case 3:
        case 4:
            for (int i = 0; i < size; ++i) {
                if ((temp == count[i].y || temp >= 750 && 0 == count[i].y
                     || temp < 0 && (750 - volume) == count[i].y)
                    && count[0].x == count[i].x) {
                    return true;
                }
            }
            return false;
            break;
        }
        return false;
    }

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(head);
        for (int i = 0; i <= 8; ++i) {
            target.draw(rectangle[i]);
        }
    }

    void update()
    {
        head.setPosition(sf::Vector2f(count[0].x, count[0].y));
        for (int i = 1; i < size - 1; ++i) {
            rectangle[i].setPosition(
                    sf::Vector2f(count[i - 1].x, count[i - 1].y));
        }
    }

    snake() : volume(50), head(volume / 2)
    {
        this->size = 10;
        count[0].x = 500;
        count[0].y = 350;
        this->volume = 50;
        for (int i = 1; i < size; ++i) {
            count[i].x = count[i - 1].x - volume;
            count[i].y = count[i - 1].y;
        }

        head.setPosition(sf::Vector2f(count[0].x, count[0].y));

        for (int i = 0; i < size - 1; ++i) {
            rectangle[i] = sf::RectangleShape(
                    sf::Vector2f(count[i + 1].x, count[i + 1].y));
            rectangle[i].setSize(sf::Vector2f(volume, volume));
            rectangle[i].setPosition(count[i + 1].x, count[i + 1].y);
        }

        for (int i = size - 1; i < 9; ++i) {
            rectangle[i] = sf::RectangleShape(
                    sf::Vector2f(count[i + 1].x, count[i + 1].y));
            rectangle[i].setSize(sf::Vector2f(volume, volume));
            rectangle[i].setPosition(count[i + 1].x, count[i + 1].y);
            // rectangle[i].setFillColor(sf::Color::Black);
        }
    }

    bool movement(int expression)
    {
        int temp;
        switch (expression) {
        case (1):
            temp = count[0].x + volume;
            if (check(temp, 1)) {
                return true;
                break;
            }
            for (int i = size - 1; i > 0; --i) {
                count[i].x = count[i - 1].x;
                count[i].y = count[i - 1].y;
                transition(i);
            }
            count[0].x += volume;
            transition(0);
            break;
        case (2):
            temp = count[0].x - volume;
            if (check(temp, 2)) {
                return true;
                break;
            }
            for (int i = size - 1; i > 0; --i) {
                count[i].x = count[i - 1].x;
                count[i].y = count[i - 1].y;
                transition(i);
            }
            count[0].x -= volume;
            transition(0);
            break;
        case (3):
            temp = count[0].y + volume;
            if (check(temp, 3)) {
                return true;
                break;
            }
            for (int i = size - 1; i > 0; --i) {
                count[i].y = count[i - 1].y;
                count[i].x = count[i - 1].x;
                transition(i);
            }
            count[0].y += volume;
            transition(0);
            break;
        case (4):
            temp = count[0].y - volume;
            if (check(temp, 4)) {
                return true;
                break;
            }
            for (int i = size - 1; i > 0; --i) {
                count[i].y = count[i - 1].y;
                count[i].x = count[i - 1].x;
                transition(i);
            }
            count[0].y -= volume;
            transition(0);
            break;
        }
        return false;
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
    sf::Text dead;
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
        settings.setPosition(300, 200);

        exit.setFont(font);
        exit.setString("Exit");
        exit.setCharacterSize(100);
        exit.setFillColor(sf::Color::Red);
        exit.setPosition(400, 300);

        dead.setFont(font);
        dead.setString("You dead");
        dead.setCharacterSize(100);
        dead.setFillColor(sf::Color::White);
        dead.setPosition(250, 300);

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

    sf::Text getDead()
    {
        return dead;
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
};