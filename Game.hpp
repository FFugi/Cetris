//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_GAME_HPP
#define CETRIS_GAME_HPP


#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Shape.hpp"

class Game {
public:
    Game() : window(sf::VideoMode(winWidth, winHeight), "Cetris", sf::Style::Close), board(width, height) {
        board.setTileSize(tileSize);
    }

    void run() {
        clock.restart();
        resetShape();
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    std::cout << "pressed" << std::endl;
                    switch (event.key.code) {
                        case sf::Keyboard::A:
                            shape.slide(-1);
                            break;
                        case sf::Keyboard::D:
                            shape.slide(1);
                            break;
                        case sf::Keyboard::W:
                            break;
                        case sf::Keyboard::S:
                            break;
                        default:
                            break;
                    }
                }
            }

            if (clock.getElapsedTime().asMilliseconds() > static_cast<int>(step)) {
                clock.restart();
                Coord coord = shape.getCoord();
                if (coord.y == static_cast<int>(height - 1) || board.getField({coord.x, coord.y + 1})) {
                    board.setField(shape.getCoord(), true);
                    resetShape();
                } else {
                    shape.doStep();
                }
            }
            window.clear(sf::Color::Black);

            window.draw(board);
            window.draw(shape.getTile());

            window.display();
        }
    }

private:
    unsigned width = 10;
    unsigned height = 10;
    unsigned step = 500;
    unsigned tileSize = 30;
    int winWidth = width * tileSize;
    int winHeight = height * tileSize;
    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window;
    Board board;
    Shape shape;

    void resetShape() {
        shape.setCoord({static_cast<int>(width) / 2, 0});
    }
};


#endif //CETRIS_GAME_HPP
