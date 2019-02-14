//
// Created by ffugi on 14.02.19.
//

#ifndef CETRIS_SHAPEGENERATOR_HPP
#define CETRIS_SHAPEGENERATOR_HPP


#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Structs.hpp"
#include "Shape.hpp"

class ShapeGenerator {
public:
    ShapeGenerator() = default;

    Shape getRandomShape() const;

    Shape getShapeByName(std::string &name) const;

    void addShapeCoords(const std::string &name, const Shape &shape);

private:
    std::map<std::string, Shape> shapes;
};


#endif //CETRIS_SHAPEGENERATOR_HPP
