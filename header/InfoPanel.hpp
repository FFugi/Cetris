//
// Created by ffugi on 14.02.19.
//

#ifndef CETRIS_INFOBOX_HPP
#define CETRIS_INFOBOX_HPP


#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "GameProperties.hpp"
#include "Observer.hpp"

class InfoPanel : public sf::Drawable, public sf::Transformable, public Observer {
public:
    InfoPanel(std::shared_ptr<GameProperties> observedProps);

    void setDimensions(int width, int height);

    void setScore(int value);

    void setClears(int value);

    void setLevel(int value);

    void setFont(const sf::Font &font);

    void update() override;

private:
    sf::Text scoreText;
    sf::Text linesText;
    sf::Text levelText;
    sf::RectangleShape background;
    int outlineThickness;
    int numberBuffer;
    std::shared_ptr<GameProperties> observedProps;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //CETRIS_INFOBOX_HPP
