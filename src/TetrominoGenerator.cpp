//
// Created by ffugi on 14.02.19.
//

#include "TetrominoGenerator.hpp"

Tetromino TetrominoGenerator::getRandomTetromino() {
    // TODO better randomization
    if (currentBag.empty()){
        std::vector<std::string> names;
        for (const auto &shape : tetrominos) {
            names.push_back(shape.first);
        }
        for (unsigned i = 0; i < 7; i++) {
            unsigned long index = rand() % names.size();
            currentBag.push(names.at(index));
            names.erase(names.begin() + index);
        }
    }

    auto name = currentBag.top();
    currentBag.pop();
    return tetrominos.at(name);
}

Tetromino TetrominoGenerator::getTetrominoByName(std::string &name) const {
    return tetrominos.at(name);
}

void TetrominoGenerator::addTetrominoCoords(const std::string &name, const Tetromino &tetromino) {
    tetrominos.insert_or_assign(name, tetromino);
}
