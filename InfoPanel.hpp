//
// Created by ffugi on 14.02.19.
//

#ifndef CETRIS_INFOBOX_HPP
#define CETRIS_INFOBOX_HPP


#include <SFML/Graphics.hpp>
#include <iostream>

class InfoPanel : public sf::Drawable, public sf::Transformable  {
public:
    InfoPanel();

    void setDimensions(int width, int height);

    void setScore(int value);

    void setClears(int value);

    void setFont(const sf::Font &font);

private:
    sf::Text scoreText;
    sf::Text linesText;
    sf::RectangleShape background;
    int outlineThickness = 4;
    int numberBuffer = 5;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //CETRIS_INFOBOX_HPP
