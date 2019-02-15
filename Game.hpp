//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_GAME_HPP
#define CETRIS_GAME_HPP


#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Shape.hpp"
#include "ShapeGenerator.hpp"
#include "InfoPanel.hpp"

class Game {
public:
    Game() : window(sf::VideoMode(winWidth, winHeight), "Cetris", sf::Style::Close), board(width, height) {
        assignShapesToGenerator();
        board.setTileSize(tileSize);
        infoPanel.setDimensions(winWidth, 30);
        infoPanel.setPosition(0, winHeight - 30);
    }

    void run();

    void pollEvents();

private:
    unsigned width = 10;
    unsigned height = 16;
    unsigned step = 700;
    unsigned tileSize = 30;
    int winWidth = width * tileSize;
    int winHeight = height * tileSize + 30;
    int score = 0;
    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window;
    InfoPanel infoPanel;
    Board board;
    Shape shape;
    ShapeGenerator generator;
    bool isStopped = false;

    void doStep();

    void assignShapesToGenerator();

    bool isCoordOccupied(const std::vector<Coord> &tiles, const Coord offset);

    void setTiles(const std::vector<Coord> &coords);

    void resetShape();

    void endGame();
};


#endif //CETRIS_GAME_HPP
