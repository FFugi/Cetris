//
// Created by ffugi on 15.02.19.
//

#ifndef CETRIS_STOPSCREEN_HPP
#define CETRIS_STOPSCREEN_HPP


#include <SFML/Graphics.hpp>

class StopPanel : public sf::Drawable, public sf::Transformable {
public:
    StopPanel();

    void setHeaderText(const std::string& value);

    void setContentText(const std::string& value);

    void setDimensions(int width, int height);

    void setFont(const sf::Font &font);

private:
    sf::Text header;
    sf::Text content;
    sf::RectangleShape outer;
    sf::RectangleShape inner;
    unsigned outlineThickness = 10;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //CETRIS_STOPSCREEN_HPP
