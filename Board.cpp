//
// Created by ffugi on 13.02.19.
//

#include "Board.hpp"

void Board::setTileSize(unsigned size) {
    tileSize = size;
}

void Board::setField(Coord coords, bool value) {
    if (!areCoordsOk(coords)) {
        throw std::out_of_range("Width or height is too high!");
    }
    fields.insert_or_assign(coords, value);
}

bool Board::getField(Coord coords) {
    if (!areCoordsOk(coords)) {
        throw std::out_of_range("Width or height is too high!");
    }
    return fields.at(coords);
}

int Board::removeFullLines() {
    int lines = 0;
    for (int y = height - 1; y >= 0; y--) {
        bool hasLine = true;
        for (int x = 0; x < width; x++) {
            if (!getField({x, y})) {
                hasLine = false;
            }
        }
        if (hasLine) {
            lines++;
            continue;
        }
        if (lines > 0) {
            for (int x = 0; x < width; x++) {
                setField({x, y + lines}, getField({x, y}));
            }
        }
    }
    return lines;
}

void Board::print() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << (fields.at({x, y}) ? '#' : '.');
        }
        std::cout << std::endl;
    }
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    unsigned size = tileSize - 2 * outlineThickness;
    sf::RectangleShape rect(sf::Vector2f(size, size));
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(outlineThickness);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (fields.at({x, y})) {
                rect.setPosition(x * tileSize + outlineThickness, y * tileSize + outlineThickness);
                target.draw(rect, states);
            }
        }
    }
}

bool Board::areCoordsOk(Coord coords) {
    return coords.x < width && coords.y < height && coords.x >= 0 && coords.y >= 0;
}
