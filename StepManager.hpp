//
// Created by ffugi on 18.02.19.
//

#ifndef CETRIS_STEPMANAGER_HPP
#define CETRIS_STEPMANAGER_HPP


#include <utility>
#include <vector>

class StepManager {
public:
    explicit StepManager(unsigned defaultStep);

    void addStep(std::pair<unsigned, unsigned> step);

    void updateStep(unsigned clearCount);

    unsigned getStep();

private:
    std::vector<std::pair<unsigned, unsigned>> stepTimes;
    unsigned defaultStep;
    unsigned step;
    unsigned currentIndex;
};


#endif //CETRIS_STEPMANAGER_HPP
