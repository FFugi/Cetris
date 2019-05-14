#include <iostream>
#include <experimental/filesystem>
#include "Game.hpp"

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    std::experimental::filesystem::path path = argv[0];
    Game game(path.parent_path().string());
    game.run();
    return 0;
}

