//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_BOARD_HPP
#define CETRIS_BOARD_HPP

#include <map>
#include <iostream>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Structs.hpp"

class Board : public sf::Drawable, public sf::Transformable {
public:
    Board(unsigned width, unsigned height) {
        this->height = height;
        this->width = width;
        for (unsigned y = 0; y < height; y++) {
            for (unsigned x = 0; x < width; x++) {
                fields.insert_or_assign({x, y}, false);
            }
        }
        std::cout << fields.size() << std::endl;
    }

    void setTileSize(unsigned size) {
        tileSize = size;
    }

    void setField(Coord coords, bool value) {
        if (coords.x >= width || coords.y >= height) {
            throw std::out_of_range("Width or height is too high!");
        }
        fields.insert_or_assign(coords, value);
        std::cout << fields.size() << std::endl;
    }

    bool getField(Coord coords) {
        if (coords.x >= width || coords.y >= height) {
            throw std::out_of_range("Width or height is too high!");
        }
        return fields.at(coords);
    }

    void print() {
        for (unsigned y = 0; y < height; y++) {
            for (unsigned x = 0; x < width; x++) {
                std::cout << (fields.at({x, y}) ? '#' : '.');
            }
            std::cout << std::endl;
        }
    }

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();

        unsigned size = tileSize - 2*outlineThickness;
        sf::RectangleShape rect(sf::Vector2f(size, size));
        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(outlineThickness);
        for (unsigned y = 0; y < height; y++) {
            for (unsigned x = 0; x < width; x++) {
                if (fields.at({x, y})) {
                    rect.setPosition(x * tileSize, y * tileSize);
                    target.draw(rect, states);
                }
            }
        }
    }

    unsigned tileSize = 30;
    unsigned outlineThickness = 4;
    unsigned width;
    unsigned height;
    std::map<Coord, bool> fields;
};


#endif //CETRIS_BOARD_HPP
