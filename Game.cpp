//
// Created by ffugi on 13.02.19.
//

#include "Game.hpp"

void Game::run() {
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
                board.removeFullLines();
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

void Game::pollEvents() {
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
            } else if (event.key.code == sf::Keyboard::S) {
                auto coords = shape.getTileCoords();
                if (!isCoordOccupied(coords, {0, 1})) {
                    shape.doStep();
                    clock.restart();
                }
            }
        }
    }
}

bool Game::isCoordOccupied(std::vector<Coord> &tiles, Coord offset) {
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

void Game::setTiles(std::vector<Coord> &coords) {
    for (auto &coord: coords) {
        board.setField(coord, true);
    }
}

void Game::resetShape() {
    Shape shape;
    this->shape = shape;
    this->shape.setCoord({static_cast<int>(width) / 2, 0});
}
