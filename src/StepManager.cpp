//
// Created by ffugi on 18.02.19.
//

#include <iostream>
#include <StepManager.hpp>

#include "StepManager.hpp"


StepManager::StepManager(unsigned defaultStep, std::shared_ptr<GameProperties> props)
    : props(std::move(props)), defaultStep(defaultStep), step(defaultStep), currentIndex(0) {
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
    unsigned prevStep = step;
    step = stepTimes[currentIndex].second;
    if (prevStep != step) {
        notify();
    }
}

unsigned StepManager::getStep() const {
    return step;
}

unsigned StepManager::getLevel() const {
    return currentIndex + 1;
}

void StepManager::reset() {
    currentIndex = 0;
    notify();
}

void StepManager::update() {
    updateStep(props->getClears());
}

