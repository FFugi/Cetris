#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    int width = 800;
    int height = 800;
    sf::RenderWindow window(sf::VideoMode(width, height), "Cetris", sf::Style::Close);
    sf::Event event;

    while (window.isOpen()){
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // +++++
        window.clear(sf::Color::Black);
        window.display();
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}