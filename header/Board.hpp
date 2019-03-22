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


/**
 * Class which contains tetrominos which were placed
 * It's drawable and transformable so can be used like SFML-entity
 */
class Board : public sf::Drawable, public sf::Transformable {
public:
    /**
     * Costructor - initializes board of given width and height
     * @param width - width of board (number of fields)
     * @param height - height of board (number of fields)
     */
    Board(int width, int height) :
        tileSize(30), outlineThickness(4),
        width(width), height(height) {
        clear();
    }

    /**
     * Sets tile size (pixels)
     * @param size - size of tile (pixels)
     */
    void setTileSize(unsigned size);

    /**
     * Gets size of tile (pixels)
     * @return size of tile (pixels)
     */
    unsigned getTileSize();

    /**
     * Sets given field as taken of free
     * @param coords - coords of field to be set
     * @param value - true when taken, false when free
     */
    void setField(Coord coords, bool value);

    /**
     * Gets value representing field
     * @param coords - coords of field
     * @return true when field is taken, false when free
     */
    bool getField(Coord coords) const;

    /**
     * Removes rows which contain only taken fields
     * and moves higher places on their place
     * @return - number of rows removed
     */
    int removeFullLines();

    /**
     * Prints board in stdout
     */
    void print() const;

    /**
     * Sets all fields as free
     */
    void clear();

private:

    /**
     * SFML derived method used to draw
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * Checks if coords fit into size of board
     * @param coords - coords to be checked
     * @return true when fit, false if not
     */
    bool doCoordsFit(Coord coords) const;

    unsigned tileSize;
    unsigned outlineThickness;
    int width;
    int height;
    std::map<Coord, bool> fields;
};


#endif //CETRIS_BOARD_HPP
