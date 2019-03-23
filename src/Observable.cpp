//
// Created by ffugi on 23.03.19.
//

#include "Observable.hpp"


void Observable::notify() const {
    for (const auto &o : observers) {
        o->update();
    }
}

void Observable::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(std::move(observer));
}

void Observable::removeObserver(std::shared_ptr<Observer> observer) {
    // TODO
}
