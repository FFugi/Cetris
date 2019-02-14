#include <utility>

//
// Created by ffugi on 13.02.19.
//

#include "Shape.hpp"

void Shape::rotate(Direction direction) {
    if (isRotatable) {
        for (auto &coord : tiles) {
            Coord newCoord;
            if (direction == Direction::LEFT) {
                newCoord.x = coord.y;
                newCoord.y = -coord.x;
            } else {
                newCoord.x = -coord.y;
                newCoord.y = coord.x;
            }
            coord = newCoord;
        }
    }
}

void Shape::setTileSize(unsigned size) {
    tileSize = size;
}

void Shape::doStep() {
    coord.y++;
}

void Shape::slide(int position) {
    coord.x += position;
}

void Shape::setCoord(Coord coord) {
    this->coord = coord;
}

void Shape::setRotatable(bool value) {
    isRotatable = true;
}

void Shape::updateTilePos(sf::RectangleShape &tile, Coord offset) const {
    tile.setPosition((coord.x + offset.x) * tileSize, (coord.y + offset.y) * tileSize);
}

Coord Shape::getCoord() {
    return coord;
}

const std::vector<Coord> Shape::getTileCoords() {
    std::vector<Coord> coords;
    for (auto coord : tiles) {
        coords.push_back({coord.x + this->coord.x, coord.y + this->coord.y});
    }
    return coords;
}

void Shape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));

    for (auto &offset : tiles) {
        updateTilePos(tile, offset);
        target.draw(tile, states);
    }
}

void Shape::setTileCoords(std::vector<Coord> coords) {
    this->tiles = std::move(coords);
}
