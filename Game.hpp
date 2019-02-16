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
#include "StopPanel.hpp"

class Game {
public:
    Game();

    void run();

    void pollEvents();

private:
    unsigned width = 10;
    unsigned height = 16;
    unsigned step = 700;
    unsigned tileSize = 30;
    int barHeight = 50;
    int winWidth = (width + 1) * tileSize;
    int winHeight = height * tileSize + tileSize / 2 + barHeight;
    int score = 0;
    int clears = 0;
    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window;
    InfoPanel infoPanel;
    StopPanel stopPanel;
    Board board;
    Shape shape;
    ShapeGenerator generator;
    sf::Font font;
    bool isStopped = false;

    void doStep();

    void assignShapesToGenerator();

    bool isCoordOccupied(const std::vector<Coord> &tiles, const Coord offset);

    void setTiles(const std::vector<Coord> &coords);

    void resetShape();

    void endGame();

    void restartGame();
};


#endif //CETRIS_GAME_HPP
