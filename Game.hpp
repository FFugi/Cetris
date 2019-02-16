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
    Game() : window(sf::VideoMode(winWidth, winHeight), "Cetris", sf::Style::Close), board(width, height) {
        assignShapesToGenerator();
        board.setTileSize(tileSize);

        if (!font.loadFromFile("VCR_OSD_MONO_1.001.ttf")) {
            std::cerr << "Couldn't load font file VCR_OSD_MONO_1.001.ttf!" << std::endl;
            exit(1);
        }
        infoPanel.setFont(font);
        stopPanel.setFont(font);
        infoPanel.setDimensions(winWidth, 30);
        infoPanel.setPosition(0, winHeight - 30);
        stopPanel.setDimensions(250, 200);
        stopPanel.setOrigin(125, 100);
        stopPanel.setPosition(winWidth / 2, winHeight / 2);
    }

    void run();

    void pollEvents();

private:
    unsigned width = 10;
    unsigned height = 16;
    unsigned step = 700;
    unsigned tileSize = 30;
    int winWidth = (width + 1) * tileSize;
    int winHeight = height * tileSize + tileSize / 2 + 30;
    int score = 0;
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
};


#endif //CETRIS_GAME_HPP
