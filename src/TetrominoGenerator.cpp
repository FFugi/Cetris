//
// Created by ffugi on 14.02.19.
//

#include "TetrominoGenerator.hpp"

Tetromino TetrominoGenerator::getRandomTetromino() const {
    // TODO better randomization
    int shapeToReturn = static_cast<int>(rand() % tetrominos.size());
    int iterator = 0;
    std::string name;
    for (const auto &shape : tetrominos) {
        if (iterator == shapeToReturn) {
            name = shape.first;
        }
        iterator++;
    }
    return tetrominos.at(name);
}

Tetromino TetrominoGenerator::getTetrominoByName(std::string &name) const {
    return tetrominos.at(name);
}

void TetrominoGenerator::addTetrominoCoords(const std::string &name, const Tetromino &shape) {
    tetrominos.insert_or_assign(name, shape);
}
