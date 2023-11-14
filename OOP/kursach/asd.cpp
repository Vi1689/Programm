#include "asd.h"

void Play(int size, int capacity)
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1000, 750), "Play");

    Apple apple(capacity);
    snake s(size, capacity);

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
                case sf::Keyboard::W:
                    if (s.check(1)) {
                        window.clear();
                        window.draw(died);
                        window.display();
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        window.close();
                    }
                    s.movement(1);
                    s.update();
                    window.clear();
                    window.draw(s);
                    window.draw(apple);
                    window.display();
                    break;
                case sf::Keyboard::S:
                    if (s.check(2)) {
                        window.clear();
                        window.draw(died);
                        window.display();
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        window.close();
                    }
                    s.movement(2);
                    s.update();
                    window.clear();
                    window.draw(s);
                    window.draw(apple);
                    window.display();
                    break;
                case sf::Keyboard::D:
                    if (s.check(3)) {
                        window.clear();
                        window.draw(died);
                        window.display();
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        window.close();
                    }
                    s.movement(3);
                    s.update();
                    window.clear();
                    window.draw(s);
                    window.draw(apple);
                    window.display();
                    break;
                case sf::Keyboard::A:
                    if (s.check(4)) {
                        window.clear();
                        window.draw(died);
                        window.display();
                        std::this_thread::sleep_for(
                                std::chrono::milliseconds(1000));
                        window.close();
                    }
                    s.movement(4);
                    s.update();
                    window.clear();
                    window.draw(s);
                    window.draw(apple);
                    window.display();
                    break;
                }
            }
            apple_node = apple.getNode();
            s_node = s.getNode();
            if (apple_node.x == s_node.x && apple_node.y == s_node.y) {
                s.AddCapacity();
                apple.movement(2);
            }
        }
    }
}

void Setting(int* size, int* capacity)
{
    sf::RenderWindow window(sf::VideoMode(1000, 750), "Setting");
    Menu menu("Size", "Capacity", "Back");

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
                    if (menu.getColor(0) == 'g') {
                        Menu menu_size("2", "4", "6");
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
                                        if (menu_size.getColor(0) == 'g') {
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
                        Menu menu_capacity("50", "25", "10");
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
                                        if (menu_capacity.getColor(0) == 'g') {
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

        Menu menu("Play", "Setting", "Exit");

        window.clear();
        window.draw(menu);
        window.display();

        int size = 2, capacity = 50;

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
                        if (menu.getColor(0) == 'g') {
                            Play(size, capacity);
                            break;
                        } else if (menu.getColor(1) == 'g') {
                            Setting(&size, &capacity);
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