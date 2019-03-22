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
#include "StepManager.hpp"


class Game {
public:
    Game();

    void run();

private:
    unsigned width;
    unsigned height;
    unsigned score;
    unsigned clears;
    bool isStopped;

    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window;
    sf::Font font;

    InfoPanel infoPanel;
    StopPanel stopPanel;
    Board board;
    Shape shape;
    ShapeGenerator generator;
    StepManager stepManager;

    void pollEvents();

    bool doStep();

    void assignShapesToGenerator();

    bool isCoordOccupied(const std::vector<Coord> &tiles, const Coord offset) const;

    void setTiles(const std::vector<Coord> &coords);

    void resetShape();

    void endGame();

    void restartGame();
};


#endif //CETRIS_GAME_HPP
