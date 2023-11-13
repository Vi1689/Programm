#include "oke.h"

// g++ laba_3_1var.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 750), "SFML works!");
    snake s;
    bool flag;

    sf::CircleShape head(s.getVolume() / 2);

    head.setPosition(sf::Vector2f(s.getX(0), s.getY(0)));

    sf::RectangleShape rectangle1(sf::Vector2f(s.getX(1), s.getY(1)));

    rectangle1.setSize(sf::Vector2f(s.getVolume(), s.getVolume()));

    rectangle1.setPosition(s.getX(1), s.getY(1));

    sf::RectangleShape rectangle2(sf::Vector2f(s.getX(2), s.getY(2)));

    rectangle2.setSize(sf::Vector2f(s.getVolume(), s.getVolume()));

    rectangle2.setPosition(s.getX(2), s.getY(2));

    sf::RectangleShape rectangle3(sf::Vector2f(s.getX(3), s.getY(3)));

    rectangle3.setSize(sf::Vector2f(s.getVolume(), s.getVolume()));

    rectangle3.setPosition(s.getX(3), s.getY(3));

    menu Menu;

    window.clear();
    window.draw(Menu.getPlay());
    window.draw(Menu.getSettings());
    window.draw(Menu.getExit());
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
                    Menu.Down();
                    window.clear();
                    window.draw(Menu.getPlay());
                    window.draw(Menu.getSettings());
                    window.draw(Menu.getExit());
                    window.display();
                    break;
                case sf::Keyboard::Up:
                    Menu.Up();
                    window.clear();
                    window.draw(Menu.getPlay());
                    window.draw(Menu.getSettings());
                    window.draw(Menu.getExit());
                    window.display();
                    break;
                case sf::Keyboard::Enter:
                    if (Menu.getColor(0) == 'g') {
                        window.clear();
                        window.draw(head);
                        window.draw(rectangle1);
                        window.draw(rectangle2);
                        window.draw(rectangle3);
                        window.display();
                        while (window.isOpen()) {
                            while (window.pollEvent(event)) {
                                if (event.type == sf::Event::Closed) {
                                    window.close();
                                    break;
                                }
                                if (event.type == sf::Event::KeyPressed) {
                                    switch (event.key.code) {
                                    case sf::Keyboard::S:
                                        s.movement(3);
                                        head.setPosition(s.getX(0), s.getY(0));
                                        rectangle1.setPosition(s.getX(1), s.getY(1));
                                        rectangle2.setPosition(s.getX(2), s.getY(2));
                                        rectangle3.setPosition(s.getX(3), s.getY(3));
                                        window.clear();
                                        window.draw(head);
                                        window.draw(rectangle1);
                                        window.draw(rectangle2);
                                        window.draw(rectangle3);
                                        window.display();
                                        break;
                                    case sf::Keyboard::W:
                                        s.movement(4);
                                        head.setPosition(s.getX(0), s.getY(0));
                                        rectangle1.setPosition(s.getX(1), s.getY(1));
                                        rectangle2.setPosition(s.getX(2), s.getY(2));
                                        rectangle3.setPosition(s.getX(3), s.getY(3));
                                        window.clear();
                                        window.draw(head);
                                        window.draw(rectangle1);
                                        window.draw(rectangle2);
                                        window.draw(rectangle3);
                                        window.display();
                                        break;
                                    case sf::Keyboard::D:
                                        s.movement(1);
                                        head.setPosition(s.getX(0), s.getY(0));
                                        rectangle1.setPosition(s.getX(1), s.getY(1));
                                        rectangle2.setPosition(s.getX(2), s.getY(2));
                                        rectangle3.setPosition(s.getX(3), s.getY(3));
                                        window.clear();
                                        window.draw(head);
                                        window.draw(rectangle1);
                                        window.draw(rectangle2);
                                        window.draw(rectangle3);
                                        window.display();
                                        break;
                                    case sf::Keyboard::A:
                                        s.movement(2);
                                        head.setPosition(s.getX(0), s.getY(0));
                                        rectangle1.setPosition(s.getX(1), s.getY(1));
                                        rectangle2.setPosition(s.getX(2), s.getY(2));
                                        rectangle3.setPosition(s.getX(3), s.getY(3));
                                        window.clear();
                                        window.draw(head);
                                        window.draw(rectangle1);
                                        window.draw(rectangle2);
                                        window.draw(rectangle3);
                                        window.display();
                                        break;
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
                        window.draw(Menu.getPlay());
                        window.draw(Menu.getSettings());
                        window.draw(Menu.getExit());
                        window.display();
                        break;
                    } else if (Menu.getColor(1) == 'g') {
                        window.close();
                        break;
                    } else if (Menu.getColor(2) == 'g') {
                        window.close();
                        break;
                    }
                }
            }
        }
    }

    return 0;
}