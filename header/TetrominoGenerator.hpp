//
// Created by ffugi on 14.02.19.
//

#ifndef CETRIS_TETROMINOGENERATOR_HPP
#define CETRIS_TETROMINOGENERATOR_HPP


#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Structs.hpp"
#include "Tetromino.hpp"

class TetrominoGenerator {
public:
    TetrominoGenerator() = default;

    Tetromino getRandomTetromino() const;

    Tetromino getTetrominoByName(std::string &name) const;

    void addTetrominoCoords(const std::string &name, const Tetromino &shape);

private:
    std::map<std::string, Tetromino> tetrominos;
};


#endif //CETRIS_TETROMINOGENERATOR_HPP
