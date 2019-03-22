//
// Created by ffugi on 18.02.19.
//

#ifndef CETRIS_HELPERS_HPP
#define CETRIS_HELPERS_HPP

namespace Helpers {
    int digitsNumber(int number) {
        if (number < 10) {
            return 1;
        }
        int digits = 0;
        while (number > 0) {
            number /= 10;
            digits++;
        }
        return digits;
    }

    std::string getSpaces(int number) {
        std::string spaces;
        spaces.insert(0, static_cast<unsigned long>(number), ' ');
        return spaces;
    }
}

#endif //CETRIS_HELPERS_HPP
