//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_SHAPE_HPP
#define CETRIS_SHAPE_HPP

#include <SFML/Graphics.hpp>
#include "Structs.hpp"

class Shape : public sf::Drawable, public sf::Transformable {
public:
    Shape() {
        tiles.push_back({-1, 0});
        tiles.push_back({0, 0});
        tiles.push_back({1, 0});
        tiles.push_back({2, 0});
    }

    void rotate(Direction direction) {
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

    void setTileSize(unsigned size) {
        tileSize = size;
    }

    void doStep() {
        coord.y++;
    }

    void slide(int position) {
        coord.x += position;
    }

    void setCoord(Coord coord) {
        this->coord = coord;
    }

    void setRotatable(bool value) {
        isRotatable = true;
    }

    void updateTilePos(sf::RectangleShape &tile, Coord offset) const {
        tile.setPosition((coord.x + offset.x) * tileSize, (coord.y + offset.y) * tileSize);
    }

    Coord getCoord() {
        return coord;
    }

    const std::vector<Coord> getTileCoords() {
        std::vector<Coord> coords;
        for (auto coord : tiles) {
            coords.push_back({coord.x + this->coord.x, coord.y + this->coord.y});
        }
        return coords;
    }

private:
    Coord coord = {0, 0};
    std::vector<Coord> tiles;
    unsigned tileSize = 30;
    bool isRotatable = true;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));

        for (auto &offset : tiles) {
            updateTilePos(tile, offset);
            target.draw(tile, states);
        }
    }
};


#endif //CETRIS_SHAPE_HPP
