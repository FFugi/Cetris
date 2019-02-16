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
        clear();
    }

    void setTileSize(unsigned size);

    void setField(Coord coords, bool value);

    bool getField(Coord coords);

    int removeFullLines();

    void print();

    void clear();

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    bool areCoordsOk(Coord coords);

    unsigned tileSize = 30;
    unsigned outlineThickness = 4;
    int width;
    int height;
    std::map<Coord, bool> fields;
};


#endif //CETRIS_BOARD_HPP
