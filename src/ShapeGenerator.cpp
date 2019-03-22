//
// Created by ffugi on 14.02.19.
//

#include "ShapeGenerator.hpp"

Shape ShapeGenerator::getRandomShape() const {
    // TODO better randomization
    int shapeToReturn = static_cast<int>(rand() % shapes.size());
    int iterator = 0;
    std::string name;
    for (const auto &shape : shapes) {
        if (iterator == shapeToReturn) {
            name = shape.first;
        }
        iterator++;
    }
    return shapes.at(name);
}

Shape ShapeGenerator::getShapeByName(std::string &name) const {
    return shapes.at(name);
}

void ShapeGenerator::addShapeCoords(const std::string &name, const Shape &shape) {
    shapes.insert_or_assign(name, shape);
}
