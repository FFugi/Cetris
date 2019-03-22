//
// Created by ffugi on 15.02.19.
//

#include "StopPanel.hpp"

StopPanel::StopPanel() {
    header.setString("Header");
    content.setString("Content");
    header.setCharacterSize(24);
    content.setCharacterSize(16);
    outer.setOutlineThickness(outlineThickness);
    outer.setOutlineColor(sf::Color::Black);
    outer.setFillColor(sf::Color::White);
    inner.setFillColor(sf::Color::Black);
}

void StopPanel::setHeaderText(const std::string &value) {
    header.setString(value);
}

void StopPanel::setContentText(const std::string &value) {
    content.setString(value);
}

void StopPanel::setDimensions(int width, int height) {
    outer.setSize(sf::Vector2f(width - 2 * outlineThickness, height - 2 * outlineThickness));
    inner.setSize(sf::Vector2f(width - 4 * outlineThickness, height - 4 * outlineThickness));
    outer.setPosition(outlineThickness, outlineThickness);
    inner.setPosition(2 * outlineThickness, 2 * outlineThickness);
    header.setPosition(3 * outlineThickness, 3 * outlineThickness);
    content.setPosition(3 * outlineThickness, 7 * outlineThickness);
}

void StopPanel::setFont(const sf::Font &font) {
    header.setFont(font);
    content.setFont(font);
}

void StopPanel::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(outer, states);
    target.draw(inner, states);
    target.draw(header, states);
    target.draw(content, states);
}
