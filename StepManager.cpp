//
// Created by ffugi on 18.02.19.
//

#include "StepManager.hpp"

StepManager::StepManager(unsigned defaultStep) : defaultStep(defaultStep), step(defaultStep), currentIndex(0) {

}

void StepManager::addStep(std::pair<unsigned, unsigned> step) {
    stepTimes.push_back(step);
}

void StepManager::updateStep(unsigned clearCount) {
    if (stepTimes.empty()) {
        step = defaultStep;
        return;
    }
    while (currentIndex < stepTimes.size() - 1 && stepTimes[currentIndex].first <= clearCount) {
        currentIndex++;
    }
    step = stepTimes[currentIndex].second;
}

unsigned StepManager::getStep() {
    return step;
}
