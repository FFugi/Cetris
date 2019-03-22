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
    Shape ghostShape;
    ShapeGenerator generator;
    StepManager stepManager;

    void pollEvents();

    bool doStep();

    unsigned getPlacementOffset() {
        auto coords = shape.getTileCoords();
        int val = 1;
        while (!isCoordOccupied(coords, {0, val})) {
            val++;
        }
        return static_cast<unsigned>(val - 1);
    }

    void updateGhost() {
        unsigned offset = getPlacementOffset();
        auto coord = shape.getCoord();
        coord.y += offset;
        ghostShape.setCoord(coord);
    }

    void assignShapesToGenerator();

    bool isCoordOccupied(const std::vector<Coord> &tiles, const Coord offset) const;

    void setTiles(const std::vector<Coord> &coords);

    void resetShape();

    void endGame();

    void restartGame();

    void moveShape(Direction dir) {
        switch(dir){
            case Direction::DOWN:
                shape.doStep();
                break;
            case Direction::LEFT:
                shape.slide(-1);
                break;
            case Direction::RIGHT:
                shape.slide(1);
                break;
            default:
                break;
        }
        updateGhost();
    }

    void rotateShape(RotationDir rot) {
        shape.rotate(rot);
        ghostShape.rotate(rot);
        updateGhost();
    }
};


#endif //CETRIS_GAME_HPP
