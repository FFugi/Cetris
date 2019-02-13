//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_SHAPE_HPP
#define CETRIS_SHAPE_HPP

#include <SFML/Graphics.hpp>
#include "Structs.hpp"

class Shape {
public:
    Shape() : tile(sf::Vector2f(tileSize, tileSize)) {

    }

    void setTileSize(unsigned size) {
        tileSize = size;
    }

    sf::RectangleShape getTile() {
        return tile;
    }

    void doStep(){
        coord.y++;
        updateTilePos();
    }

    void slide(int position){
        coord.x += position;
        updateTilePos();
    }

    void setCoord(Coord coord) {
        this->coord = coord;
        updateTilePos();
    }

    void updateTilePos() {
        tile.setPosition(coord.x * tileSize, coord.y * tileSize);
    }

    Coord getCoord() {
        return coord;
    }

private:
    unsigned tileSize = 30;
    sf::RectangleShape tile;
    Coord coord = {0,0};
};


#endif //CETRIS_SHAPE_HPP
