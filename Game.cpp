//
// Created by ffugi on 13.02.19.
//

#include "Game.hpp"

void Game::run() {
    clock.restart();
    resetShape();
    while (window.isOpen()) {
        pollEvents();

        if (!isStopped && clock.getElapsedTime().asMilliseconds() > static_cast<int>(step)) {
            doStep();
        }
        window.clear(sf::Color::Black);

        window.draw(board);
        window.draw(shape);
        window.draw(infoPanel);

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
                if (event.key.code == sf::Keyboard::A) {
                    if (!isCoordOccupied(coords, {-1, 0})) {
                        shape.slide(-1);
                    }
                } else if (event.key.code == sf::Keyboard::D) {
                    if (!isCoordOccupied(coords, {1, 0})) {
                        shape.slide(1);
                    }
                } else if (event.key.code == sf::Keyboard::W) {
                    shape.rotate(Direction::RIGHT);
                    coords = shape.getTileCoords();
                    if (isCoordOccupied(coords, {0, 0})) {
                        shape.rotate(Direction::LEFT);
                    }
                } else if (event.key.code == sf::Keyboard::S) {
                    doStep();
                }
            }
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

bool Game::isCoordOccupied(const std::vector<Coord> &tiles, const Coord offset) {
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
    this->shape = generator.getRandomShape();
    this->shape.setCoord({static_cast<int>(width) / 2, 0});
}

void Game::assignShapesToGenerator() {
    // ####
    std::vector<Coord> longCoords;
    Shape longShape;
    longCoords.push_back({-1, 0});
    longCoords.push_back({0, 0});
    longCoords.push_back({1, 0});
    longCoords.push_back({2, 0});
    longShape.setTileCoords(longCoords);
    generator.addShapeCoords("long", longShape);

    // ##
    // ##
    std::vector<Coord> boxCoords;
    Shape boxShape;
    boxCoords.push_back({-1, 0});
    boxCoords.push_back({0, 0});
    boxCoords.push_back({-1, 1});
    boxCoords.push_back({0, 1});
    boxShape.setRotatable(false);
    boxShape.setTileCoords(boxCoords);
    generator.addShapeCoords("box", boxShape);

    //  ##
    // ##
    std::vector<Coord> zigZagCoordsRight;
    Shape zigZagShapeRight;
    zigZagCoordsRight.push_back({-1, 1});
    zigZagCoordsRight.push_back({0, 1});
    zigZagCoordsRight.push_back({0, 0});
    zigZagCoordsRight.push_back({1, 0});
    zigZagShapeRight.setTileCoords(zigZagCoordsRight);
    generator.addShapeCoords("zigZagRight", zigZagShapeRight);

    // ##
    //  ##
    std::vector<Coord> zigZagCoordsLeft;
    Shape zigZagShapeLeft;
    zigZagCoordsLeft.push_back({-1, 0});
    zigZagCoordsLeft.push_back({0, 1});
    zigZagCoordsLeft.push_back({0, 0});
    zigZagCoordsLeft.push_back({1, 1});
    zigZagShapeLeft.setTileCoords(zigZagCoordsLeft);
    generator.addShapeCoords("zigZagLeft", zigZagShapeLeft);

    // ###
    //  #
    std::vector<Coord> podiumCoords;
    Shape podiumShape;
    podiumCoords.push_back({-1, 0});
    podiumCoords.push_back({0, 0});
    podiumCoords.push_back({1, 0});
    podiumCoords.push_back({0, 1});
    podiumShape.setTileCoords(podiumCoords);
    generator.addShapeCoords("podium", podiumShape);

    // ###
    // #
    std::vector<Coord> LCoordsLeft;
    Shape LShapeLeft;
    LCoordsLeft.push_back({-1, 1});
    LCoordsLeft.push_back({-1, 0});
    LCoordsLeft.push_back({0, 0});
    LCoordsLeft.push_back({1, 0});
    LShapeLeft.setTileCoords(LCoordsLeft);
    generator.addShapeCoords("LLeft", LShapeLeft);

    // ###
    //   #
    std::vector<Coord> LCoordsRight;
    Shape LShapeRight;
    LCoordsRight.push_back({-1, 0});
    LCoordsRight.push_back({0, 0});
    LCoordsRight.push_back({1, 0});
    LCoordsRight.push_back({1, 1});
    LShapeRight.setTileCoords(LCoordsRight);
    generator.addShapeCoords("LRight", LShapeRight);
}

void Game::doStep() {
    clock.restart();
    auto coords = shape.getTileCoords();
    if (isCoordOccupied(coords, {0, 1})) {
        setTiles(coords);
        resetShape();
        if (isCoordOccupied(shape.getTileCoords(), {0, 0})) {
            endGame();
        }
        // TODO score
        switch (board.removeFullLines()) {
            case 1:
                score += 1;
                break;
            case 2:
                score += 4;
                break;
            case 3:
                score += 12;
                break;
            case 4:
                score += 20;
                break;
            default:
                break;
        }
        infoPanel.setScore(score);
    } else {
        shape.doStep();
    }
}

void Game::endGame() {
    isStopped = true;
}
