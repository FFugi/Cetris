
//
// Created by ffugi on 23.03.19.
//

#ifndef CETRIS_GAMEPROPERTIES_HPP
#define CETRIS_GAMEPROPERTIES_HPP


#include "Observable.hpp"
#include "StepManager.hpp"

class StepManager;

class GameProperties : public Observable, public Observer {
public:
    GameProperties(unsigned score, unsigned clears, unsigned level);

    unsigned getScore();

    unsigned getClears();

    unsigned getLevel();

    void addToScore(int value);

    void setScore(unsigned value);

    void incrementClears();

    void setClears(unsigned value);

    // Observer methods
    void update() override;

    void setObservable(std::shared_ptr<StepManager> observable);

private:
    unsigned score;
    unsigned clears;
    unsigned level;
    std::vector<std::shared_ptr<Observer>> observers;
    std::shared_ptr<StepManager> observable;
};


#endif //CETRIS_GAMEPROPERTIES_HPP

