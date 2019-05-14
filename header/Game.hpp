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
#include "GameProperties.hpp"
#include <memory>

/**
 * Class which contains all game logic and components such as window, font etc.
 */
class Game {
public:
    explicit Game(std::string path);

    /**
     * Runs the game until it's finished
     */
    void run();

private:
    unsigned width;
    unsigned height;
    std::shared_ptr<GameProperties> props;
    bool isStopped;

    sf::Event event;
    sf::Clock clock;
    sf::RenderWindow window;
    sf::Font font;

    StopPanel stopPanel;
    Board board;
    Tetromino tetromino;
    Tetromino ghostTetromino;
    TetrominoGenerator generator;
    std::shared_ptr<StepManager> stepManager;
    std::shared_ptr<InfoPanel> infoPanel;

    void pollEvents();

    /**
     * Moves tetromino down if possible, if not places it in the board,
     * generates new tetromino and checks if game is finished
     * @return true if tetromino was placed on board, otherwise false
     */
    bool doStep();

    /**
     * Calculates how much fields differs from tetromino to its placement in board
     * based on current tetromino position
     * @return
     */
    unsigned getPlacementOffset();

    /**
     * Updates ghost tetromino position
     */
    void updateGhost();

    /**
     * Assigns possible tetrominos to tetromino generator
     */
    void assignTetrominosToGenerator();

    /**
     * Checks if given vector of coords will collide with anything on the board
     * or will fit to the board after moving given offset
     * @param tiles - vector of coords to check
     * @param offset - offset of coords
     * @return true if will collide, false if not
     */
    bool isCoordOccupied(const std::vector<Coord> &tiles, const Coord offset) const;

    /**
     * Appends given vector of coords to board
     * @param coords - vector of coords
     */
    void setTiles(const std::vector<Coord> &coords);

    /**
     * Restarts step-clock, gets new tetromino
     */
    void resetTetromino();

    /**
     * Stops game, shows end-game panel
     */
    void endGame();

    /**
     * Restarts game - clears board, score and clear count
     */
    void restartGame();

    /**
     * Moves tetromino in given direction
     * @param dir - direction in which tetromino will move
     */
    void moveTetromino(Direction dir);

    /**
     * Rotates tetromino in given rotation type
     * @param rot - rotation type
     */
    void rotateTetromino(RotationDir rot);
};


#endif //CETRIS_GAME_HPP
