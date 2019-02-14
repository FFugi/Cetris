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

    void rotate(Direction direction);

    void setTileSize(unsigned size);

    void doStep();

    void slide(int position);

    void setTileCoords(std::vector<Coord> coords);

    void setCoord(Coord coord);

    void setRotatable(bool value);

    void updateTilePos(sf::RectangleShape &tile, Coord offset) const;

    Coord getCoord();

    const std::vector<Coord> getTileCoords();

private:
    Coord coord = {0, 0};
    std::vector<Coord> tiles;
    unsigned tileSize = 30;
    bool isRotatable = true;
    int outlineThickness = 5;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //CETRIS_SHAPE_HPP
