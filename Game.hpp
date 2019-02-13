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
            pollEvents();

            if (clock.getElapsedTime().asMilliseconds() > static_cast<int>(step)) {
                clock.restart();
                auto coords = shape.getTileCoords();
                if (isCoordOccupied(coords, {0, 1})) {
                    setTiles(coords);
                    resetShape();
                    // TODO score
                    board.checkFullLines();
                } else {
                    shape.doStep();
                }
            }
            window.clear(sf::Color::Black);

            window.draw(board);
            window.draw(shape);

            window.display();
        }
    }

    void pollEvents() {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                auto coords = shape.getTileCoords();
                if (event.key.code == sf::Keyboard::A) {
                    if (!isCoordOccupied(coords, {-1, 0})) {
                        shape.slide(-1);
                    }
                } else if (event.key.code == sf::Keyboard::D) {
                    if (!isCoordOccupied(coords, {1, 0})) {
                        shape.slide(1);
                    }
                } else if (event.key.code == sf::Keyboard::W) {
                    shape.rotate(Direction::LEFT);
                    coords = shape.getTileCoords();
                    if (isCoordOccupied(coords, {0, 0})) {
                        shape.rotate(Direction::RIGHT);
                    }
                }
            }
        }
    }

private:
    unsigned width = 16;
    unsigned height = 12;
    unsigned step = 200;
    unsigned tileSize = 30;
    int winWidth = width * tileSize;
    int winHeight = height * tileSize;
    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window;
    Board board;
    Shape shape;

    bool isCoordOccupied(std::vector<Coord> &tiles, Coord offset) {
        for (auto &tile: tiles) {
            Coord coord = {tile.x + offset.x, tile.y + offset.y};
            if (coord.y >= static_cast<int>(height)
                || coord.y < 0
                || coord.x >= static_cast<int>(width)
                || coord.x < 0
                || board.getField(coord)) {
                return true;
            }
        }
        return false;
    }

    void setTiles(std::vector<Coord> &coords) {
        for (auto &coord: coords) {
            board.setField(coord, true);
        }
    }

    void resetShape() {
        Shape shape;
        this->shape = shape;
        this->shape.setCoord({static_cast<int>(width) / 2, 0});
    }
};


#endif //CETRIS_GAME_HPP
