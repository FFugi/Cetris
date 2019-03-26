//
// Created by ffugi on 14.02.19.
//

#include "TetrominoGenerator.hpp"

std::string TetrominoGenerator::peekNextTetromino() {
    return next;
}

Tetromino TetrominoGenerator::getNextTetromino() {
    if (tetrominos.empty()) {
        throw std::out_of_range("List of possible tetrominos is empty!");
    }
    if (currentBag.empty()) {
        refillBag();
    }

    if (next.empty()) {
        next = currentBag.top();
        currentBag.pop();
    }
    auto toReturnName = next;
    next = currentBag.top();
    currentBag.pop();
    auto toReturn = tetrominos.at(toReturnName);
    toReturn.setName(toReturnName);
    return toReturn;
}

Tetromino TetrominoGenerator::getTetrominoByName(std::string &name) const {
    auto toReturn = tetrominos.at(name);
    toReturn.setName(name);
    return toReturn;
}

void TetrominoGenerator::addTetrominoCoords(const std::string &name, const Tetromino &tetromino) {
    tetrominos.insert_or_assign(name, tetromino);
}

