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
    Board(int width, int height) {
        this->height = height;
        this->width = width;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                fields.insert_or_assign({x, y}, false);
            }
        }
        std::cout << fields.size() << std::endl;
    }

    void setTileSize(unsigned size) {
        tileSize = size;
    }

    void setField(Coord coords, bool value) {
        if (!areCoordsOk(coords)) {
            std::cout << coords.x <<", "<<coords.y <<std::endl;
            throw std::out_of_range("Width or height is too high!");
        }
        fields.insert_or_assign(coords, value);
        std::cout << fields.size() << std::endl;
    }

    bool getField(Coord coords) {
        if (!areCoordsOk(coords)) {
            throw std::out_of_range("Width or height is too high!");
        }
        return fields.at(coords);
    }

    void print() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
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
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (fields.at({x, y})) {
                    rect.setPosition(x * tileSize + outlineThickness, y * tileSize + outlineThickness);
                    target.draw(rect, states);
                }
            }
        }
    }

    bool areCoordsOk(Coord coords) {
        return coords.x < width && coords.y < height && coords.x >= 0 && coords.y >= 0;
    }


    unsigned tileSize = 30;
    unsigned outlineThickness = 4;
    int width;
    int height;
    std::map<Coord, bool> fields;
};


#endif //CETRIS_BOARD_HPP
