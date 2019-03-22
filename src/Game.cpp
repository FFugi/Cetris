//
// Created by ffugi on 13.02.19.
//

#include "Game.hpp"


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
                            shape.slide(-1);
                        }
                        break;
                    }
                    case sf::Keyboard::D:{
                        if (!isCoordOccupied(coords, {1, 0})) {
                            shape.slide(1);
                        }
                        break;
                    }
                    case sf::Keyboard::W:{
                        shape.rotate(Direction::RIGHT);
                        coords = shape.getTileCoords();
                        if (isCoordOccupied(coords, {0, 0})) {
                            shape.rotate(Direction::LEFT);
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
        return true;
    }
    shape.doStep();
    return false;
}

void Game::endGame() {
    isStopped = true;
    stopPanel.setHeaderText("GAME OVER");
    stopPanel.setContentText("Your score:\n\n" + std::to_string(score) + "\n\nR -> Restart");
}

Game::Game() : window(sf::VideoMode(winWidth, winHeight), "Cetris", sf::Style::Close), board(width, height),
               stepManager(800) {
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
}

void Game::restartGame() {
    infoPanel.setScore(0);
    infoPanel.setClears(0);
    stepManager.updateStep(0);
    board.clear();
    resetShape();
    isStopped = false;
}
