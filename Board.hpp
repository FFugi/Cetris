//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_BOARD_HPP
#define CETRIS_BOARD_HPP

#include <map>
#include <iostream>
#include "Structs.hpp"

class Board {
public:
    Board(unsigned width, unsigned height) {
        this->height = height;
        this->width = width;
        for (unsigned y = 0; y < height; y++) {
            for (unsigned x = 0; x < height; x++) {
                fields.insert_or_assign({x, y}, false);
            }
        }
        std::cout << fields.size() << std::endl;
    }

    void setField(Field coords, bool value) {
        if (coords.x >= width || coords.y >= height) {
            throw std::out_of_range("Width or height is too high!");
        }
        fields.insert_or_assign(coords, value);
        std::cout << fields.size() << std::endl;
    }

    bool getField(Field coords) {
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

    unsigned width;
    unsigned height;
    std::map<Field, bool> fields;
};


#endif //CETRIS_BOARD_HPP
