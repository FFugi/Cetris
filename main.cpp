#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

int main() {
    int winWidth = 300;
    int winHeight = 500;
    unsigned width = 10;
    unsigned heigth = 10;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Cetris", sf::Style::Close);
    sf::Event event;

    Board board(width, heigth);
    board.setTileSize(winWidth/width);
    sf::RectangleShape rect(sf::Vector2f(winWidth/width, winWidth/width));

    board.setField({9, 9}, true);
    board.print();
    while (window.isOpen()){
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // +++++
        window.clear(sf::Color::Black);

        window.draw(board);

        window.display();
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}