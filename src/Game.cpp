//
// Created by ffugi on 13.02.19.
//

#include "Game.hpp"
#include <memory>


void Game::run() {
    clock.restart();
    resetTetromino();
    while (window.isOpen()) {
        pollEvents();

        if (!isStopped && clock.getElapsedTime().asMilliseconds() > static_cast<int>(stepManager.getStep())) {
            doStep();
        }
        window.clear(sf::Color::Black);

        window.draw(board);
        window.draw(ghostTetromino);
        window.draw(tetromino);
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
                auto coords = tetromino.getTileCoords();
                switch (event.key.code) {
                    case sf::Keyboard::A: {
                        if (!isCoordOccupied(coords, {-1, 0})) {
                            moveTetromino(Direction::LEFT);
                        }
                        break;
                    }
                    case sf::Keyboard::D: {
                        if (!isCoordOccupied(coords, {1, 0})) {
                            moveTetromino(Direction::RIGHT);
                        }
                        break;
                    }
                    case sf::Keyboard::W: {
                        rotateTetromino(RotationDir::CLOCKWISE);
                        coords = tetromino.getTileCoords();
                        if (isCoordOccupied(coords, {0, 0})) {
                            rotateTetromino(RotationDir::COUNTER_CLOCKWISE);
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

void Game::resetTetromino() {
    clock.restart();
    tetromino = generator.getRandomTetromino();
    tetromino.setCoord({static_cast<int>(width) / 2, 0});
    ghostTetromino = tetromino;
    ghostTetromino.setOutlineThickness(12);
    updateGhost();
}

void Game::assignTetrominosToGenerator() {
    auto tileSize = board.getTileSize();
    // ####
    std::vector<Coord> iCoords = {{-1, 0}, {0, 0}, {1, 0}, {2, 0}};
    Tetromino i(tileSize);
    i.setTileCoords(iCoords);
    generator.addTetrominoCoords("I", i);

    // ##
    // ##
    std::vector<Coord> oCoords = {{-1, 0}, {0, 0}, {-1, 1}, {0, 1}};
    Tetromino o(tileSize);
    o.setRotatable(false);
    o.setTileCoords(oCoords);
    generator.addTetrominoCoords("O", o);

    //  ##
    // ##
    std::vector<Coord> sCoords = {{-1, 1}, {0, 1}, {0, 0}, {1, 0}};
    Tetromino s(tileSize);
    s.setTileCoords(sCoords);
    generator.addTetrominoCoords("S", s);

    // ##
    //  ##
    std::vector<Coord> zCoords = {{-1, 0}, {0, 1}, {0, 0}, {1, 1}};
    Tetromino z(tileSize);
    z.setTileCoords(zCoords);
    generator.addTetrominoCoords("Z", z);

    // ###
    //  #
    std::vector<Coord> tCoords = {{-1, 0}, {0, 0}, {1, 0}, {0, 1}};
    Tetromino t(tileSize);
    t.setTileCoords(tCoords);
    generator.addTetrominoCoords("T", t);

    // ###
    // #
    std::vector<Coord> lCoords = {{-1, 1}, {-1, 0}, {0, 0}, {1, 0}};
    Tetromino l(tileSize);
    l.setTileCoords(lCoords);
    generator.addTetrominoCoords("L", l);

    // ###
    //   #
    std::vector<Coord> jCoords = {{-1, 0}, {0, 0}, {1, 0}, {1, 1}};
    Tetromino j(tileSize);
    j.setTileCoords(jCoords);
    generator.addTetrominoCoords("J", j);
}

bool Game::doStep() {
    clock.restart();
    auto coords = tetromino.getTileCoords();
    if (isCoordOccupied(coords, {0, 1})) {
        setTiles(coords);
        resetTetromino();
        if (isCoordOccupied(tetromino.getTileCoords(), {0, 0})) {
            endGame();
        }
        // TODO score
        const int lines = board.removeFullLines();
        if (lines > 0) {
            clears++;
            infoPanel.setClears(clears);
            stepManager.updateStep(clears);
            infoPanel.setLevel(stepManager.getLevel());
        }
        switch (lines) {
            case 0:
                break;
            case 1:
                score += 40;
                break;
            case 2:
                score += 100;
                break;
            case 3:
                score += 300;
                break;
            case 4:
                score += 1200;
                break;
            default:
                score += 1200;
                break;
        }
        infoPanel.setScore(score);
        updateGhost();
        return true;
    }
    moveTetromino(Direction::DOWN);
    return false;
}

void Game::endGame() {
    isStopped = true;
    stopPanel.setHeaderText("GAME OVER");
    stopPanel.setContentText("Your score:\n\n" + std::to_string(score) + "\n\nR -> Restart");
}

Game::Game() : width(10), height(20), score(0), clears(0), isStopped(false),
               board(width, height), tetromino(30), stepManager(800) {
    unsigned tileSize = 30;
    unsigned barHeight = 70;
    unsigned winWidth = (width + 1) * tileSize;
    unsigned winHeight = height * tileSize + tileSize / 2 + barHeight;
    window.create(sf::VideoMode(winWidth, winHeight), "Cetris", sf::Style::Close);
    assignTetrominosToGenerator();
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
    infoPanel.setLevel(1);
    // assign steps
    stepManager.addStep({20, 800});
    stepManager.addStep({40, 700});
    stepManager.addStep({60, 500});
    stepManager.addStep({80, 400});
    stepManager.addStep({100, 300});
    stepManager.addStep({120, 200});
    stepManager.addStep({140, 100});
}

void Game::restartGame() {
    score = 0;
    clears = 0;
    stepManager.reset();
    infoPanel.setScore(0);
    infoPanel.setClears(0);
    infoPanel.setLevel(1);
    board.clear();
    resetTetromino();
    isStopped = false;
}

unsigned Game::getPlacementOffset() {
    auto coords = tetromino.getTileCoords();
    int val = 1;
    while (!isCoordOccupied(coords, {0, val})) {
        val++;
    }
    return static_cast<unsigned>(val - 1);
}

void Game::updateGhost() {
    unsigned offset = getPlacementOffset();
    auto coord = tetromino.getCoord();
    coord.y += offset;
    ghostTetromino.setCoord(coord);
}

void Game::rotateTetromino(RotationDir rot) {
    tetromino.rotate(rot);
    ghostTetromino.rotate(rot);
    updateGhost();
}

void Game::moveTetromino(Direction dir) {
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
