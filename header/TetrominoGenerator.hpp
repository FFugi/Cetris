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


/**
 * Class which contains possible tetrominos and can generate ones randomly
 * or by given name
 */
class TetrominoGenerator {
public:
    TetrominoGenerator() = default;

    /**
     * Gets random tetromino
     * @return generated tetromino
     */
    Tetromino getRandomTetromino() const;

    /**
     * Gets tetromino basing on given name
     * @param name - name of tetromino
     * @return generated tetromino
     */
    Tetromino getTetrominoByName(std::string &name) const;

    /**
     * Adds possible tetromino to base
     * @param name - name of tetromino
     * @param tetromino - given tetromino
     */
    void addTetrominoCoords(const std::string &name, const Tetromino &tetromino);

private:
    std::map<std::string, Tetromino> tetrominos;
};


#endif //CETRIS_TETROMINOGENERATOR_HPP
