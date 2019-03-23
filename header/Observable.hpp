//
// Created by ffugi on 23.03.19.
//

#ifndef CETRIS_OBSERVABLE_HPP
#define CETRIS_OBSERVABLE_HPP

#include <memory>
#include <vector>

#include "Observer.hpp"

class Observable {
public:
    virtual void notify() const;

    virtual void addObserver(std::shared_ptr<Observer> observer);

    virtual void removeObserver(std::shared_ptr<Observer> observer);

private:
    std::vector<std::shared_ptr<Observer>> observers;
};


#endif //CETRIS_OBSERVABLE_HPP
