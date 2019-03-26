#include <utility>

//
// Created by ffugi on 14.02.19.
//

#include "InfoPanel.hpp"
#include "Helpers.hpp"
#include "GameProperties.hpp"

void InfoPanel::setDimensions(int width, int height) {
    background.setSize(sf::Vector2f(width, height - outlineThickness));
}

void InfoPanel::setScore(const int value) {
    scoreText.setString("Score:  " + Helpers::getSpaces(numberBuffer - Helpers::digitsNumber(value)) +
                        std::to_string(value));
}

void InfoPanel::setClears(const int value) {
    linesText.setString("Clears: " + Helpers::getSpaces(numberBuffer - Helpers::digitsNumber(value)) +
                        std::to_string(value));
}

void InfoPanel::setLevel(const int value) {
    levelText.setString("Level:  " + Helpers::getSpaces(numberBuffer - Helpers::digitsNumber(value)) +
                        std::to_string(value));
}

void InfoPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(background, states);
    target.draw(scoreText, states);
    target.draw(linesText, states);
    target.draw(levelText, states);
    target.draw(nextText, states);
    target.draw(tetromino, states);
}

InfoPanel::InfoPanel(std::shared_ptr<GameProperties> observedProps) :
    outlineThickness(4), numberBuffer(7), observedProps(std::move(observedProps)) {
    background.setSize(sf::Vector2f(100, 30));
    background.setFillColor(sf::Color::Black);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(outlineThickness);
    background.setPosition(0, outlineThickness);
    scoreText.setCharacterSize(16);
    scoreText.setPosition(outlineThickness, outlineThickness);
    linesText.setCharacterSize(16);
    linesText.setPosition(outlineThickness, outlineThickness + 20);
    levelText.setCharacterSize(16);
    levelText.setPosition(outlineThickness, outlineThickness + 40);
    nextText.setCharacterSize(16);
    nextText.setPosition(outlineThickness + 200, outlineThickness);
    nextText.setString("Next:");
}

void InfoPanel::setFont(const sf::Font &font) {
    scoreText.setFont(font);
    linesText.setFont(font);
    levelText.setFont(font);
    nextText.setFont(font);
}

void InfoPanel::setTetromino(const Tetromino &value) {
    tetromino = value;
    tetromino.setTileSize(20);
    tetromino.setCoord({1, 0});
    tetromino.setOffset({40, 15});
    tetromino.setPosition(background.getSize().x / 2, 10);
}

void InfoPanel::update() {
    setScore(observedProps->getScore());
    setClears(observedProps->getClears());
    setLevel(observedProps->getLevel());
    setTetromino(observedProps->getNextTetromino());
}
