#pragma once

#include <iostream>

#include "DNA.hpp"

using namespace std;

template <class T>
class Citizen {
public:
    DNA<T> dna;

    T start;

    bool done = false;

    float fitness = 0;

    Citizen(DNA<T> dna, T start) {
        this->dna = dna;
        this->start = start;
    }

    virtual float fitness_calculate(T target) {
        cerr << "Calculting fitness in citizen" << endl;
        (void) target;
        return 0.0f;
    }

    virtual float fitness_normalize(float max) {
        fitness /= max;
        return fitness;
    }

    virtual void run(T target, unsigned int count) {
        cerr << "Running citizen, are you sure this is supposed to happen?" << endl;
        (void) target;
        (void) count;
    }

    bool operator<(const Citizen<T>& cit2) const
    {
        return (this->fitness > cit2.fitness);
    }

};
