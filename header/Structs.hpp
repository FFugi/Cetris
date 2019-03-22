//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_STRUCTS_HPP
#define CETRIS_STRUCTS_HPP

struct Coord {
    int x;
    int y;

    friend bool operator<(const Coord &left, const Coord &right) {
        if (left.x < right.x) {
            return true;
        } else if (left.x > right.x) {
            return false;
        } else {
            return left.y < right.y;
        }
    }
};

enum class Direction {
    LEFT,
    RIGHT
};

#endif //CETRIS_STRUCTS_HPP
