//
// Created by ffugi on 14.02.19.
//

#ifndef CETRIS_INFOBOX_HPP
#define CETRIS_INFOBOX_HPP


#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class InfoPanel : public sf::Drawable, public sf::Transformable  {
public:
    InfoPanel();

    void setDimensions(int width, int height);

    void setScore(int value);

private:
    sf::Font font;
    sf::Text scoreText;
    sf::RectangleShape background;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //CETRIS_INFOBOX_HPP
