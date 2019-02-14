//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_GAME_HPP
#define CETRIS_GAME_HPP


#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Shape.hpp"

class Game {
public:
    Game() : window(sf::VideoMode(winWidth, winHeight), "Cetris", sf::Style::Close), board(width, height) {
        board.setTileSize(tileSize);
    }

    void run();

    void pollEvents();

private:
    unsigned width = 10;
    unsigned height = 16;
    unsigned step = 200;
    unsigned tileSize = 30;
    int winWidth = width * tileSize;
    int winHeight = height * tileSize;
    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window;
    Board board;
    Shape shape;

    bool isCoordOccupied(std::vector<Coord> &tiles, Coord offset);

    void setTiles(std::vector<Coord> &coords);

    void resetShape();
};


#endif //CETRIS_GAME_HPP
