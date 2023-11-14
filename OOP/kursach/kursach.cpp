#include "oke.h"

// g++ laba_3_1var.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
    try {
        sf::RenderWindow window(sf::VideoMode(1000, 750), "Snake");

        snake s;
        bool flag = false;
/*
        sf::CircleShape head(s.getVolume() / 2);

        head.setPosition(sf::Vector2f(s.getX(0), s.getY(0)));

        sf::RectangleShape rectangle[9];

        for (int i = 0; i < s.getSize() - 1; ++i) {
            rectangle[i] = sf::RectangleShape(sf::Vector2f(s.getX(i + 1), s.getY(i + 1)));
            rectangle[i].setSize(sf::Vector2f(s.getVolume(), s.getVolume()));
            rectangle[i].setPosition(s.getX(i + 1), s.getY(i + 1));
        }

        for (int i = s.getSize() - 1; i < 9; ++i) {
            rectangle[i] = sf::RectangleShape(sf::Vector2f(s.getX(i + 1), s.getY(i + 1)));
            rectangle[i].setSize(sf::Vector2f(s.getVolume(), s.getVolume()));
            rectangle[i].setPosition(s.getX(i + 1), s.getY(i + 1));
            // rectangle[i].setFillColor(sf::Color::Black);
        }
*/
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
                            /*
                            window.draw(head);
                            for (int i = 0; i <= 8; ++i) {
                                window.draw(rectangle[i]);
                            }
                            */
                            window.draw(s);
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
                                            if(s.movement(3)){
                                                flag = true;
                                                window.clear();
                                                window.draw(Menu.getDead());
                                                window.display();
                                                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                                                break;
                                            }
                                            s.update();
                                            window.clear();
                                            window.draw(s);
                                            window.display();
                                            break;
                                        case sf::Keyboard::W:
                                            if(s.movement(4)){
                                                flag = true;
                                                window.clear();
                                                window.draw(Menu.getDead());
                                                window.display();
                                                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                                                break;
                                            }
                                            s.update();
                                            window.clear();
                                            window.draw(s);
                                            window.display();
                                            break;
                                        case sf::Keyboard::D:
                                            if(s.movement(1)){
                                                flag = true;
                                                window.clear();
                                                window.draw(Menu.getDead());
                                                window.display();
                                                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                                                break;
                                            }
                                            s.update();
                                            window.clear();
                                            window.draw(s);
                                            window.display();
                                            break;
                                        case sf::Keyboard::A:
                                            if(s.movement(2)){
                                                flag = true;
                                                window.clear();
                                                window.draw(Menu.getDead());
                                                window.display();
                                                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                                                break;
                                            }
                                            s.update();
                                            window.clear();
                                            window.draw(s);
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

    } catch (const char* s) {
        std::cout << s << "\n";
        return 0;
    } catch (...) {
        std::cout << "Error\n";
        return 0;
    }
    
}