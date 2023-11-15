#include "kursach.h"

void Play(int size, int capacity, int speed)
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1000, 750), "Play");

    Apple apple(capacity);
    snake s(size, capacity);
    int t = 0;
    sf::Font font;
    if (!font.loadFromFile("ArialBlack.ttf")) {
        throw "No font";
    }
    sf::Text died("Died", font, 100);
    died.setFillColor(sf::Color::Red);
    died.setPosition(400, 200);

    node apple_node, s_node;

    window.clear();
    window.draw(s);
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Up:
                    if (s.check(1)) {
                        window.clear();
                        window.draw(died);
                        window.display();
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        window.close();
                    }
                    t = 1;
                    /*
                    s.movement(1);
                    s.update();
                    window.clear();
                    window.draw(apple);
                    window.draw(s);
                    window.display();
                    */
                    break;
                case sf::Keyboard::Down:
                    if (s.check(2)) {
                        window.clear();
                        window.draw(died);
                        window.display();
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        window.close();
                    }
                    t = 2;
                    /*
                    s.movement(2);
                    s.update();
                    window.clear();
                    window.draw(apple);
                    window.draw(s);
                    window.display();
                    */
                    break;
                case sf::Keyboard::Right:
                    if (s.check(3)) {
                        window.clear();
                        window.draw(died);
                        window.display();
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        window.close();
                    }
                    t = 3;
                    /*
                    s.movement(3);
                    s.update();
                    window.clear();
                    window.draw(apple);
                    window.draw(s);
                    window.display();
                    */
                    break;
                case sf::Keyboard::Left:
                    if (s.check(4)) {
                        window.clear();
                        window.draw(died);
                        window.display();
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        window.close();
                    }
                    t = 4;
                    /*
                    s.movement(4);
                    s.update();
                    window.clear();
                    window.draw(apple);
                    window.draw(s);
                    window.display();
                    */
                    break;
                }
            }
            apple_node = apple.getNode();
            s_node = s.getNode();
            if (apple_node.x == s_node.x && apple_node.y == s_node.y) {
                s.AddSize();
                apple.movement();
            }
        }
        if (s.check(t)) {
            window.clear();
            window.draw(died);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            window.close();
        }
        s.movement(t);
        s.update();
        window.clear();
        window.draw(apple);
        window.draw(s);
        window.display();
        apple_node = apple.getNode();
        s_node = s.getNode();
        if (apple_node.x == s_node.x && apple_node.y == s_node.y) {
            s.AddSize();
            apple.movement();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}

void Setting(int* size, int* capacity, int* speed)
{
    sf::RenderWindow window(sf::VideoMode(1000, 750), "Setting");

    std::vector<std::string> str;
    str.push_back("Size");
    str.push_back("Capacity");
    str.push_back("Speed");
    str.push_back("Back");

    Menu menu(str);

    window.clear();
    window.draw(menu);
    window.display();

    bool flag = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Down:
                    menu.Down();
                    window.clear();
                    window.draw(menu);
                    window.display();
                    break;
                case sf::Keyboard::Up:
                    menu.Up();
                    window.clear();
                    window.draw(menu);
                    window.display();
                    break;
                case sf::Keyboard::Enter:
                    if (menu.getColor() == 'g') {
                        std::vector<std::string> str;
                        str.push_back("2");
                        str.push_back("4");
                        str.push_back("6");
                        str.push_back("Back");
                        Menu menu_size(str);
                        window.clear();
                        window.draw(menu_size);
                        window.display();
                        while (window.isOpen()) {
                            sf::Event event;
                            while (window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed) {
                                    window.close();
                                }
                                if (event.type == sf::Event::KeyPressed) {
                                    switch (event.key.code) {
                                    case sf::Keyboard::Down:
                                        menu_size.Down();
                                        window.clear();
                                        window.draw(menu_size);
                                        window.display();
                                        break;
                                    case sf::Keyboard::Up:
                                        menu_size.Up();
                                        window.clear();
                                        window.draw(menu_size);
                                        window.display();
                                        break;
                                    case sf::Keyboard::Enter:
                                        if (menu_size.getColor() == 'g') {
                                            (*size) = 2;
                                            break;
                                        } else if (
                                                menu_size.getColor(1) == 'g') {
                                            (*size) = 4;
                                            break;
                                        } else if (
                                                menu_size.getColor(2) == 'g') {
                                            (*size) = 6;
                                            break;
                                        } else {
                                            flag = true;
                                            break;
                                        }
                                    case sf::Keyboard::Escape:
                                        flag = true;
                                        break;
                                    }
                                }
                            }
                            if (flag) {
                                flag = false;
                                break;
                            }
                        }
                        window.clear();
                        window.draw(menu);
                        window.display();
                        break;
                    } else if (menu.getColor(1) == 'g') {
                        std::vector<std::string> str;
                        str.push_back("50");
                        str.push_back("25");
                        str.push_back("10");
                        str.push_back("Back");
                        Menu menu_capacity(str);
                        window.clear();
                        window.draw(menu_capacity);
                        window.display();
                        while (window.isOpen()) {
                            sf::Event event;
                            while (window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed) {
                                    window.close();
                                }
                                if (event.type == sf::Event::KeyPressed) {
                                    switch (event.key.code) {
                                    case sf::Keyboard::Down:
                                        menu_capacity.Down();
                                        window.clear();
                                        window.draw(menu_capacity);
                                        window.display();
                                        break;
                                    case sf::Keyboard::Up:
                                        menu_capacity.Up();
                                        window.clear();
                                        window.draw(menu_capacity);
                                        window.display();
                                        break;
                                    case sf::Keyboard::Enter:
                                        if (menu_capacity.getColor() == 'g') {
                                            (*capacity) = 50;
                                            break;
                                        } else if (
                                                menu_capacity.getColor(1)
                                                == 'g') {
                                            (*capacity) = 25;
                                            break;
                                        } else if (
                                                menu_capacity.getColor(2)
                                                == 'g') {
                                            (*capacity) = 10;
                                            break;
                                        } else {
                                            flag = true;
                                            break;
                                        }
                                    case sf::Keyboard::Escape:
                                        flag = true;
                                        break;
                                    }
                                }
                            }
                            if (flag) {
                                flag = false;
                                break;
                            }
                        }
                        window.clear();
                        window.draw(menu);
                        window.display();
                        break;
                    } else if (menu.getColor(2) == 'g') {
                        std::vector<std::string> str;
                        str.push_back("500");
                        str.push_back("250");
                        str.push_back("100");
                        str.push_back("50");
                        str.push_back("Back");
                        Menu menu_speed(str);
                        window.clear();
                        window.draw(menu_speed);
                        window.display();
                        while (window.isOpen()) {
                            sf::Event event;
                            while (window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed) {
                                    window.close();
                                }
                                if (event.type == sf::Event::KeyPressed) {
                                    switch (event.key.code) {
                                    case sf::Keyboard::Down:
                                        menu_speed.Down();
                                        window.clear();
                                        window.draw(menu_speed);
                                        window.display();
                                        break;
                                    case sf::Keyboard::Up:
                                        menu_speed.Up();
                                        window.clear();
                                        window.draw(menu_speed);
                                        window.display();
                                        break;
                                    case sf::Keyboard::Enter:
                                        if (menu_speed.getColor() == 'g') {
                                            (*speed) = 500;
                                            break;
                                        } else if (
                                                menu_speed.getColor(1) == 'g') {
                                            (*speed) = 250;
                                            break;
                                        } else if (
                                                menu_speed.getColor(2) == 'g') {
                                            (*speed) = 100;
                                            break;
                                        } else if (
                                                menu_speed.getColor(3) == 'g') {
                                            (*speed) = 50;
                                            break;
                                        } else {
                                            flag = true;
                                            break;
                                        }
                                    case sf::Keyboard::Escape:
                                        flag = true;
                                        break;
                                    }
                                }
                            }
                            if (flag) {
                                flag = false;
                                break;
                            }
                        }
                        window.clear();
                        window.draw(menu);
                        window.display();
                        break;
                    } else {
                        window.close();
                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    try {
        sf::RenderWindow window(sf::VideoMode(1000, 750), "Snake");

        std::vector<std::string> str;
        str.push_back("Play");
        str.push_back("Setting");
        str.push_back("Exit");

        Menu menu(str);

        window.clear();
        window.draw(menu);
        window.display();

        int size = 2, capacity = 50, speed = 100;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                    case sf::Keyboard::Down:
                        menu.Down();
                        window.clear();
                        window.draw(menu);
                        window.display();
                        break;
                    case sf::Keyboard::Up:
                        menu.Up();
                        window.clear();
                        window.draw(menu);
                        window.display();
                        break;
                    case sf::Keyboard::Enter:
                        if (menu.getColor() == 'g') {
                            Play(size, capacity, speed);
                            break;
                        } else if (menu.getColor(1) == 'g') {
                            Setting(&size, &capacity, &speed);
                            break;
                        } else {
                            window.close();
                            break;
                        }
                    }
                }
            }
        }
        return 0;
    } catch (const char* s) {
        std::cout << s << "\n";
        return 0;
    } catch (...) {
        std::cout << "Error"
                  << "\n";
        return 0;
    }
}