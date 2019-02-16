//
// Created by ffugi on 14.02.19.
//

#include "InfoPanel.hpp"

void InfoPanel::setDimensions(int width, int height) {
    background.setSize(sf::Vector2f(width, height - outlineThickness));
}

void InfoPanel::setScore(const int value) {
    scoreText.setString("Score: " + std::to_string(value));
}

void InfoPanel::setClears(const int value) {
    linesText.setString("Clears: " + std::to_string(value));
}

void InfoPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(background, states);
    target.draw(scoreText, states);
    target.draw(linesText, states);
}

InfoPanel::InfoPanel() {
    background.setSize(sf::Vector2f(100, 30));
    background.setFillColor(sf::Color::Black);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(outlineThickness);
    background.setPosition(0, outlineThickness);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(outlineThickness, outlineThickness);
    linesText.setCharacterSize(20);
    linesText.setPosition(outlineThickness, outlineThickness + 20);
}

void InfoPanel::setFont(const sf::Font &font) {
    scoreText.setFont(font);
    linesText.setFont(font);
}
