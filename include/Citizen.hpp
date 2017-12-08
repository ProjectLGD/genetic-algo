#pragma once

#include "DNA.hpp"

#include <iostream>

using namespace std;

template <class T>
class Citizen {
public:
    DNA<T> dna;

    T start;

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

};
