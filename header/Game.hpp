//
// Created by ffugi on 13.02.19.
//

#ifndef CETRIS_GAME_HPP
#define CETRIS_GAME_HPP


#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Tetromino.hpp"
#include "TetrominoGenerator.hpp"
#include "InfoPanel.hpp"
#include "StopPanel.hpp"
#include "StepManager.hpp"

/**
 * Class which contains all game logic and components such as window, font etc.
 */
class Game {
public:
    Game();

    /**
     * Runs the game until it's finished
     */
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
    Tetromino tetromino;
    Tetromino ghostTetromino;
    TetrominoGenerator generator;
    StepManager stepManager;

    void pollEvents();

    bool doStep();

    unsigned getPlacementOffset();

    void updateGhost();

    void assignTetrominosToGenerator();

    bool isCoordOccupied(const std::vector<Coord> &tiles, const Coord offset) const;

    void setTiles(const std::vector<Coord> &coords);

    void resetTetromino();

    void endGame();

    void restartGame();

    void moveTetromino(Direction dir) {
        switch(dir){
            case Direction::DOWN:
                tetromino.doStep();
                break;
            case Direction::LEFT:
                tetromino.slide(-1);
                break;
            case Direction::RIGHT:
                tetromino.slide(1);
                break;
            default:
                break;
        }
        updateGhost();
    }

    void rotateTetromino(RotationDir rot) {
        tetromino.rotate(rot);
        ghostTetromino.rotate(rot);
        updateGhost();
    }
};


#endif //CETRIS_GAME_HPP
