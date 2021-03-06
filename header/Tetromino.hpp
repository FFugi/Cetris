//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_TETROMINO_HPP
#define CETRIS_TETROMINO_HPP

#include <SFML/Graphics.hpp>
#include "Structs.hpp"

class Tetromino : public sf::Drawable, public sf::Transformable {
public:
    explicit Tetromino(unsigned tileSize = 30) : offset({0, 0}), coord({0, 0}),
                                                 tileSize(tileSize),
                                                 isRotatable(true), outlineThickness(6) {
        tiles.push_back({0, 0});
    }

    void rotate(RotationDir rotation);

    void setTileSize(unsigned size);

    void setOutlineThickness(unsigned thickness);

    void setOffset(std::pair<float, float> value);

    void doStep();

    void slide(int position);

    void setTileCoords(std::vector<Coord> coords);

    void setCoord(Coord coord);

    void setRotatable(bool value);

    void updateTilePos(sf::RectangleShape &tile, Coord offset) const;

    void setName(std::string &value);

    std::string &getName();

    Coord getCoord();

    const std::vector<Coord> getTileCoords();

private:
    std::pair<float, float> offset;
    Coord coord;
    std::vector<Coord> tiles;
    std::string name;
    unsigned tileSize;
    bool isRotatable;
    int outlineThickness;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //CETRIS_TETROMINO_HPP
