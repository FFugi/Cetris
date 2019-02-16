//
// Created by ffugi on 14.02.19.
//

#include "InfoPanel.hpp"

void InfoPanel::setDimensions(int width, int height) {
    background.setSize(sf::Vector2f(width, height));
}

void InfoPanel::setScore(int value) {
    scoreText.setString("Score: " + std::to_string(value));
}

void InfoPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(background, states);
    target.draw(scoreText, states);
}

InfoPanel::InfoPanel() {
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(20);
    background.setSize(sf::Vector2f(100, 30));
    background.setFillColor(sf::Color(150, 150, 150));
}

void InfoPanel::setFont(const sf::Font &font) {
    scoreText.setFont(font);
}
