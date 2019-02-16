//
// Created by ffugi on 15.02.19.
//

#ifndef CETRIS_STOPSCREEN_HPP
#define CETRIS_STOPSCREEN_HPP


#include <SFML/Graphics.hpp>

class StopPanel : public sf::Drawable, public sf::Transformable {
public:
    StopPanel() {
        header.setString("Header");
        content.setString("Content");
        header.setCharacterSize(30);
        content.setCharacterSize(20);
        outer.setOutlineThickness(outlineThickness);
        outer.setOutlineColor(sf::Color::Black);
        outer.setFillColor(sf::Color::White);
        inner.setFillColor(sf::Color::Black);
    }

    void setHeaderText(const std::string& value) {
        header.setString(value);
    }

    void setContentText(const std::string& value) {
        content.setString(value);
    }

    void setDimensions(int width, int height) {
        outer.setSize(sf::Vector2f(width - 2 * outlineThickness, height - 2 * outlineThickness));
        inner.setSize(sf::Vector2f(width - 4 * outlineThickness, height - 4 * outlineThickness));
        outer.setPosition(outlineThickness, outlineThickness);
        inner.setPosition(2 * outlineThickness, 2 * outlineThickness);
        header.setPosition(3 * outlineThickness, 3 * outlineThickness);
        content.setPosition(3 * outlineThickness, 7 * outlineThickness);
    }

    void setFont(const sf::Font &font) {
        header.setFont(font);
        content.setFont(font);
    }

private:
    sf::Text header;
    sf::Text content;
    sf::RectangleShape outer;
    sf::RectangleShape inner;
    unsigned outlineThickness = 10;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        states.transform *= getTransform();

        target.draw(outer, states);
        target.draw(inner, states);
        target.draw(header, states);
        target.draw(content, states);
    }
};


#endif //CETRIS_STOPSCREEN_HPP
