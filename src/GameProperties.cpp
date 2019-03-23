#include <utility>

//
// Created by ffugi on 23.03.19.
//

#include "GameProperties.hpp"

GameProperties::GameProperties(unsigned score, unsigned clears, unsigned level) :
    score(score), clears(clears), level(level) {
}

unsigned GameProperties::getScore() {
    return score;
}

unsigned GameProperties::getClears() {
    return clears;
}

unsigned GameProperties::getLevel() {
    return level;
}

void GameProperties::addToScore(int value) {
    score += value;
    notify();
}

void GameProperties::setScore(unsigned value) {
    if (value != score) {
        score = value;
        notify();
    }
}

void GameProperties::incrementClears() {
    clears++;
    notify();
}

void GameProperties::setClears(unsigned value) {
    if (value != clears) {
        clears = value;
        notify();
    }
}

void GameProperties::update() {
    level = observable->getLevel();
    notify();
}

void GameProperties::setObservable(std::shared_ptr<StepManager> observable) {
    this->observable = std::move(observable);
}
