//
// Created by ffugi on 13.02.19.
//

#include "Game.hpp"
#include <memory>


void Game::run() {
    clock.restart();
    resetShape();
    while (window.isOpen()) {
        pollEvents();

        if (!isStopped && clock.getElapsedTime().asMilliseconds() > static_cast<int>(stepManager.getStep())) {
            doStep();
        }
        window.clear(sf::Color::Black);

        window.draw(board);
        window.draw(ghostShape);
        window.draw(shape);
        window.draw(infoPanel);
        if (isStopped) {
            window.draw(stopPanel);
        }

        window.display();
    }
}

void Game::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (!isStopped) {
                auto coords = shape.getTileCoords();
                switch (event.key.code) {
                    case sf::Keyboard::A: {
                        if (!isCoordOccupied(coords, {-1, 0})) {
                            moveShape(Direction::LEFT);
                        }
                        break;
                    }
                    case sf::Keyboard::D: {
                        if (!isCoordOccupied(coords, {1, 0})) {
                            moveShape(Direction::RIGHT);
                        }
                        break;
                    }
                    case sf::Keyboard::W: {
                        rotateShape(RotationDir::CLOCKWISE);
                        coords = shape.getTileCoords();
                        if (isCoordOccupied(coords, {0, 0})) {
                            rotateShape(RotationDir::COUNTER_CLOCKWISE);
                        }
                        break;
                    }
                    case sf::Keyboard::S: {
                        doStep();
                        break;
                    }
                    case sf::Keyboard::X: {
                        while (!doStep());
                        break;
                    }
                    default:
                        break;
                }
            } else {
                if (event.key.code == sf::Keyboard::R) {
                    restartGame();
                }
            }
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

bool Game::isCoordOccupied(const std::vector<Coord> &tiles, const Coord offset) const {
    for (auto &tile: tiles) {
        Coord coord = {tile.x + offset.x, tile.y + offset.y};
        if (coord.y >= static_cast<int>(height)
            || coord.y < 0
            || coord.x >= static_cast<int>(width)
            || coord.x < 0
            || board.getField(coord)) {
            return true;
        }
    }
    return false;
}

void Game::setTiles(const std::vector<Coord> &coords) {
    for (auto &coord: coords) {
        board.setField(coord, true);
    }
}

void Game::resetShape() {
    clock.restart();
    shape = generator.getRandomShape();
    shape.setCoord({static_cast<int>(width) / 2, 0});
    ghostShape = shape;
    ghostShape.setOutlineThickness(12);
    updateGhost();
}

void Game::assignShapesToGenerator() {
    auto tileSize = board.getTileSize();
    // ####
    std::vector<Coord> longCoords = {{-1, 0}, {0, 0}, {1, 0}, {2, 0}};
    Shape longShape(tileSize);
    longShape.setTileCoords(longCoords);
    generator.addShapeCoords("long", longShape);

    // ##
    // ##
    std::vector<Coord> boxCoords = {{-1, 0}, {0, 0}, {-1, 1}, {0, 1}};
    Shape boxShape(tileSize);
    boxShape.setRotatable(false);
    boxShape.setTileCoords(boxCoords);
    generator.addShapeCoords("box", boxShape);

    //  ##
    // ##
    std::vector<Coord> zigZagCoordsRight = {{-1, 1}, {0, 1}, {0, 0}, {1, 0}};
    Shape zigZagShapeRight(tileSize);
    zigZagShapeRight.setTileCoords(zigZagCoordsRight);
    generator.addShapeCoords("zigZagRight", zigZagShapeRight);

    // ##
    //  ##
    std::vector<Coord> zigZagCoordsLeft = {{-1, 0}, {0, 1}, {0, 0}, {1, 1}};
    Shape zigZagShapeLeft(tileSize);
    zigZagShapeLeft.setTileCoords(zigZagCoordsLeft);
    generator.addShapeCoords("zigZagLeft", zigZagShapeLeft);

    // ###
    //  #
    std::vector<Coord> podiumCoords = {{-1, 0}, {0, 0}, {1, 0}, {0, 1}};
    Shape podiumShape(tileSize);
    podiumShape.setTileCoords(podiumCoords);
    generator.addShapeCoords("podium", podiumShape);

    // ###
    // #
    std::vector<Coord> LCoordsLeft = {{-1, 1}, {-1, 0}, {0, 0}, {1, 0}};
    Shape lShapeLeft(tileSize);
    lShapeLeft.setTileCoords(LCoordsLeft);
    generator.addShapeCoords("LLeft", lShapeLeft);

    // ###
    //   #
    std::vector<Coord> LCoordsRight = {{-1, 0}, {0, 0}, {1, 0}, {1, 1}};
    Shape lShapeRight(tileSize);
    lShapeRight.setTileCoords(LCoordsRight);
    generator.addShapeCoords("LRight", lShapeRight);
}

bool Game::doStep() {
    clock.restart();
    auto coords = shape.getTileCoords();
    if (isCoordOccupied(coords, {0, 1})) {
        setTiles(coords);
        resetShape();
        if (isCoordOccupied(shape.getTileCoords(), {0, 0})) {
            endGame();
        }
        // TODO score
        const int lines = board.removeFullLines();
        if (lines > 0) {
            clears++;
            infoPanel.setClears(clears);
            stepManager.updateStep(clears);
        }
        switch (lines) {
            case 0:
                break;
            case 1:
                score += 1;
                break;
            case 2:
                score += 5;
                break;
            case 3:
                score += 20;
                break;
            case 4:
                score += 40;
                break;
            default:
                score += 40;
                break;
        }
        infoPanel.setScore(score);
        updateGhost();
        return true;
    }
    moveShape(Direction::DOWN);
    return false;
}

void Game::endGame() {
    isStopped = true;
    stopPanel.setHeaderText("GAME OVER");
    stopPanel.setContentText("Your score:\n\n" + std::to_string(score) + "\n\nR -> Restart");
}

Game::Game() : width(10), height(20), score(0), clears(0), isStopped(false),
               board(width, height), shape(30), stepManager(800) {
    unsigned tileSize = 30;
    unsigned barHeight = 50;
    unsigned winWidth = (width + 1) * tileSize;
    unsigned winHeight = height * tileSize + tileSize / 2 + barHeight;
    window.create(sf::VideoMode(winWidth, winHeight), "Cetris", sf::Style::Close);
    assignShapesToGenerator();
    board.setTileSize(tileSize);
    if (!font.loadFromFile("../Fleftex_M.ttf")) {
        std::cerr << "Couldn't load font file Fleftex_M.ttf!" << std::endl;
        exit(1);
    }
    infoPanel.setFont(font);
    stopPanel.setFont(font);
    infoPanel.setDimensions(winWidth, barHeight);
    infoPanel.setPosition(0, winHeight - barHeight);
    stopPanel.setDimensions(250, 250);
    stopPanel.setOrigin(125, 125);
    stopPanel.setPosition(winWidth / 2, winHeight / 2);
    infoPanel.setScore(score);
    infoPanel.setClears(clears);
    // assign steps
    stepManager.addStep({5, 800});
    stepManager.addStep({10, 700});
    stepManager.addStep({15, 500});
    stepManager.addStep({25, 400});
    stepManager.addStep({35, 300});
    stepManager.addStep({50, 200});
    stepManager.addStep({75, 100});
}

void Game::restartGame() {
    infoPanel.setScore(0);
    infoPanel.setClears(0);
    stepManager.updateStep(0);
    board.clear();
    resetShape();
    isStopped = false;
}

unsigned Game::getPlacementOffset() {
    auto coords = shape.getTileCoords();
    int val = 1;
    while (!isCoordOccupied(coords, {0, val})) {
        val++;
    }
    return static_cast<unsigned>(val - 1);
}

void Game::updateGhost() {
    unsigned offset = getPlacementOffset();
    auto coord = shape.getCoord();
    coord.y += offset;
    ghostShape.setCoord(coord);
}
