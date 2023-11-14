#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

struct node {
    int x, y;
};

class entity : public sf::Drawable {
protected:
    int size, capacity;

public:
    entity()
    {
        this->size = 2;
        this->capacity = 50;
    }

    entity(int capacity)
    {
        this->size = 2;
        this->capacity = capacity;
    }

    entity(int size, int capacity)
    {
        this->size = size;
        this->capacity = capacity;
    }

    virtual node getNode() = 0;

    virtual void movement(int expression) = 0;
};

class Apple : public entity {
private:
    node position;
    sf::CircleShape apple;

public:
    Apple() : entity(), apple(capacity / 2)
    {
        position.x = 0;
        position.y = 0;
        apple.setFillColor(sf::Color::Red);
        apple.setPosition(sf::Vector2f(position.x, position.y));
    }

    Apple(int capacity) : entity(capacity), apple(capacity / 2)
    {
        position.x = 0;
        position.y = 0;
        apple.setFillColor(sf::Color::Red);
        apple.setPosition(sf::Vector2f(position.x, position.y));
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(apple);
    }

    virtual node getNode()
    {
        return position;
    }

    virtual void movement(int expression)
    {
        position.x = 500;
        position.y = 350;
        apple.setPosition(sf::Vector2f(position.x, position.y));
    }
};

class snake : public entity {
private:
    std::vector<node> count;
    sf::CircleShape head;
    std::vector<sf::RectangleShape> body;

    void transition(int i)
    {
        if (count[i].x >= 1000) {
            count[i].x = 0;
        }
        if (count[i].x < 0) {
            count[i].x = 1000 - capacity;
        }
        if (count[i].y >= 750) {
            count[i].y = 0;
        }
        if (count[i].y < 0) {
            count[i].y = 750 - capacity;
        }
    }

public:
    snake() : entity(), head(capacity / 2)
    {
        node a;
        a.x = 750;
        a.y = 500;
        count.push_back(a);
        head.setPosition(sf::Vector2f(count[0].x, count[0].y));
        head.setFillColor(sf::Color::Green);
        for (int i = 1; i < size; ++i) {
            node b;
            b.x = count[i - 1].x - capacity;
            b.y = count[i - 1].y;
            count.push_back(b);
        }
        for (int i = 0; i < size - 1; ++i) {
            sf::RectangleShape c(sf::Vector2f(capacity, capacity));
            if (i % 2) {
                c.setFillColor(sf::Color::Green);
            }
            c.setPosition(sf::Vector2f(count[i + 1].x, count[i + 1].y));
            body.push_back(c);
        }
    }

    snake(int capacity) : entity(capacity), head(capacity / 2)
    {
        node a;
        a.x = 750;
        a.y = 500;
        count.push_back(a);
        head.setPosition(sf::Vector2f(count[0].x, count[0].y));
        head.setFillColor(sf::Color::Green);
        for (int i = 1; i < size; ++i) {
            node b;
            b.x = count[i - 1].x - capacity;
            b.y = count[i - 1].y;
            count.push_back(b);
        }
        for (int i = 0; i < size - 1; ++i) {
            sf::RectangleShape c(sf::Vector2f(capacity, capacity));
            if (i % 2) {
                c.setFillColor(sf::Color::Green);
            }
            c.setPosition(sf::Vector2f(count[i + 1].x, count[i + 1].y));
            body.push_back(c);
        }
    }

    snake(int size, int capacity) : entity(size, capacity), head(capacity / 2)
    {
        node a;
        a.x = 500;
        a.y = 350;
        count.push_back(a);
        head.setPosition(sf::Vector2f(count[0].x, count[0].y));
        head.setFillColor(sf::Color::Green);
        for (int i = 1; i < size; ++i) {
            node b;
            b.x = count[i - 1].x - capacity;
            b.y = count[i - 1].y;
            count.push_back(b);
        }
        for (int i = 0; i < size - 1; ++i) {
            sf::RectangleShape c(sf::Vector2f(capacity, capacity));
            if (i % 2) {
                c.setFillColor(sf::Color::Green);
            }
            c.setPosition(sf::Vector2f(count[i + 1].x, count[i + 1].y));
            body.push_back(c);
        }
    }

    void AddCapacity()
    {
        size++;
        node b;
        b.x = count[size - 1].x - capacity;
        b.y = count[size - 1].y;
        count.push_back(b);
        sf::RectangleShape c(sf::Vector2f(capacity, capacity));
        if (body.size() % 2) {
            c.setFillColor(sf::Color::Green);
        }
        c.setPosition(sf::Vector2f(count[body.size()].x, count[body.size()].y));
        body.push_back(c);
    }

    virtual void movement(int expression)
    {
        int temp;
        switch (expression) {
        case 1:
            temp = count[0].y - capacity;
            if ((temp == count[1].y || temp >= 750 && 0 == count[1].y
                 || temp < 0 && (750 - capacity) == count[1].y)
                && count[0].x == count[1].x) {
                break;
            }
            for (int i = size - 1; i > 0; --i) {
                count[i].x = count[i - 1].x;
                count[i].y = count[i - 1].y;
                transition(i);
            }
            count[0].y -= capacity;
            transition(0);
            break;
        case 2:
            temp = count[0].y + capacity;
            if ((temp == count[1].y || temp >= 750 && 0 == count[1].y
                 || temp < 0 && (750 - capacity) == count[1].y)
                && count[0].x == count[1].x) {
                break;
            }
            for (int i = size - 1; i > 0; --i) {
                count[i].x = count[i - 1].x;
                count[i].y = count[i - 1].y;
                transition(i);
            }
            count[0].y += capacity;
            transition(0);
            break;
        case 3:
            temp = count[0].x + capacity;
            if ((temp == count[1].x || temp >= 1000 && 0 == count[1].x
                 || temp < 0 && (1000 - capacity) == count[1].x)
                && count[0].y == count[1].y) {
                break;
            }
            for (int i = size - 1; i > 0; --i) {
                count[i].x = count[i - 1].x;
                count[i].y = count[i - 1].y;
                transition(i);
            }
            count[0].x += capacity;
            transition(0);
            break;
        case 4:
            temp = count[0].x - capacity;
            if ((temp == count[1].x || temp >= 1000 && 0 == count[1].x
                 || temp < 0 && (1000 - capacity) == count[1].x)
                && count[0].y == count[1].y) {
                break;
            }
            for (int i = size - 1; i > 0; --i) {
                count[i].x = count[i - 1].x;
                count[i].y = count[i - 1].y;
                transition(i);
            }
            count[0].x -= capacity;
            transition(0);
            break;
        }
    }

    bool check(int expression)
    {
        int temp;
        switch (expression) {
        case 1:
            temp = count[0].y - capacity;
            for (int i = 2; i < body.size(); ++i) {
                if ((temp == count[i].y || temp >= 750 && 0 == count[i].y
                     || temp < 0 && (750 - capacity) == count[i].y)
                    && count[0].x == count[i].x) {
                    return true;
                }
            }
            break;
        case 2:
            temp = count[0].y + capacity;
            for (int i = 2; i < body.size(); ++i) {
                if ((temp == count[i].y || temp >= 750 && 0 == count[i].y
                     || temp < 0 && (750 - capacity) == count[i].y)
                    && count[0].x == count[i].x) {
                    return true;
                }
            }
            break;
        case 3:
            temp = count[0].x + capacity;
            for (int i = 2; i < body.size(); ++i) {
                if ((temp == count[i].x || temp >= 1000 && 0 == count[i].x
                     || temp < 0 && (1000 - capacity) == count[i].x)
                    && count[0].y == count[i].y) {
                    return true;
                }
            }
            break;
        case 4:
            temp = count[0].x - capacity;
            for (int i = 2; i < body.size(); ++i) {
                if ((temp == count[i].x || temp >= 1000 && 0 == count[i].x
                     || temp < 0 && (1000 - capacity) == count[i].x)
                    && count[0].y == count[i].y) {
                    return true;
                }
            }
            break;
        }
        return false;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(head);
        for (int i = 0; i < body.size(); ++i) {
            target.draw(body[i]);
        }
    }

    void update()
    {
        head.setPosition(sf::Vector2f(count[0].x, count[0].y));
        for (int i = 0; i < body.size(); ++i) {
            body[i].setPosition(sf::Vector2f(count[i + 1].x, count[i + 1].y));
        }
    }

    virtual node getNode()
    {
        return count[0];
    }
};

class Menu : public sf::Drawable {
private:
    sf::Text arr[3];
    char color[3] = {'g', 'r', 'r'};
    sf::Font font;

    void inittext(sf::Text& arr, sf::String s, char color, int x, int y)
    {
        arr.setFont(font);
        arr.setString(s);
        arr.setCharacterSize(100);
        if (color == 'g') {
            arr.setFillColor(sf::Color::Green);
        } else {
            arr.setFillColor(sf::Color::Red);
        }
        arr.setPosition(x, y);
    }

public:
    Menu(std::string s1, std::string s2, std::string s3)
    {
        if (!font.loadFromFile("ArialBlack.ttf")) {
            throw "No font";
        }
        inittext(arr[0], s1, 'g', 300, 100);
        inittext(arr[1], s2, 'r', 300, 200);
        inittext(arr[2], s3, 'r', 300, 300);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (int i = 0; i < 3; ++i) {
            target.draw(arr[i]);
        }
    }

    void Up()
    {
        for (int i = 0; i < 3; ++i) {
            if (color[i] == 'g') {
                if (!i) {
                    arr[i].setFillColor(sf::Color::Red);
                    arr[2].setFillColor(sf::Color::Green);
                    color[i] = 'r';
                    color[2] = 'g';
                    break;
                }
                arr[i].setFillColor(sf::Color::Red);
                arr[i - 1].setFillColor(sf::Color::Green);
                color[i] = 'r';
                color[i - 1] = 'g';
                break;
            }
        }
    }

    void Down()
    {
        for (int i = 0; i < 3; ++i) {
            if (color[i] == 'g') {
                if (i == 2) {
                    arr[i].setFillColor(sf::Color::Red);
                    arr[0].setFillColor(sf::Color::Green);
                    color[i] = 'r';
                    color[0] = 'g';
                    break;
                }
                arr[i].setFillColor(sf::Color::Red);
                arr[i + 1].setFillColor(sf::Color::Green);
                color[i] = 'r';
                color[i + 1] = 'g';
                break;
            }
        }
    }

    char getColor(int i)
    {
        return color[i];
    }
};
