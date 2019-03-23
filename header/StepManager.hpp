//
// Created by ffugi on 18.02.19.
//

#ifndef CETRIS_STEPMANAGER_HPP
#define CETRIS_STEPMANAGER_HPP


#include <utility>
#include <vector>
#include <memory>
#include "Observer.hpp"
#include "GameProperties.hpp"

class GameProperties;

class StepManager : public Observer, public Observable {
public:
    StepManager(unsigned defaultStep, std::shared_ptr<GameProperties> props);

    void addStep(std::pair<unsigned, unsigned> step);

    void updateStep(unsigned clearCount);

    void reset();

    unsigned getStep() const;

    unsigned getLevel() const;

    // Observer method
    void update() override;

private:
    std::shared_ptr<GameProperties> props;
    std::vector<std::pair<unsigned, unsigned>> stepTimes;
    unsigned defaultStep;
    unsigned step;
    unsigned currentIndex;
};


#endif //CETRIS_STEPMANAGER_HPP
