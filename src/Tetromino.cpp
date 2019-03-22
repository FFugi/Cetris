#include <utility>

//
// Created by ffugi on 13.02.19.
//

#include "Tetromino.hpp"

void Tetromino::rotate(RotationDir rotation) {
    if (isRotatable) {
        for (auto &coord : tiles) {
            Coord newCoord;
            if (rotation == RotationDir::COUNTER_CLOCKWISE) {
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

void Tetromino::setTileSize(unsigned size) {
    tileSize = size;
}

void Tetromino::doStep() {
    coord.y++;
}

void Tetromino::slide(int position) {
    coord.x += position;
}

void Tetromino::setCoord(Coord coord) {
    this->coord = coord;
}

void Tetromino::setRotatable(bool value) {
    isRotatable = value;
}

void Tetromino::updateTilePos(sf::RectangleShape &tile, Coord offset) const {
    tile.setPosition(tileSize / 2 + outlineThickness + (coord.x + offset.x) * tileSize,
                     outlineThickness + (coord.y + offset.y) * tileSize);
}

Coord Tetromino::getCoord() {
    return coord;
}

const std::vector<Coord> Tetromino::getTileCoords() {
    std::vector<Coord> coords;
    for (auto coord : tiles) {
        coords.push_back({coord.x + this->coord.x, coord.y + this->coord.y});
    }
    return coords;
}

void Tetromino::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    sf::RectangleShape tile(sf::Vector2f(tileSize - 2 * outlineThickness, tileSize - 2 * outlineThickness));
    tile.setFillColor(sf::Color::White);
    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(outlineThickness);

    for (auto &offset : tiles) {
        updateTilePos(tile, offset);
        target.draw(tile, states);
    }
}

void Tetromino::setTileCoords(std::vector<Coord> coords) {
    this->tiles = std::move(coords);
}

void Tetromino::setOutlineThickness(unsigned thickness) {
    if (2 * thickness <= tileSize) {
        outlineThickness = thickness;
    }
}
