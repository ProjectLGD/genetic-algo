#pragma once

#include "Vec3.h"
#include "Citizen.hpp"
#include "DNA.hpp"


class Rocket : public Citizen<Vec3> {
public:
    Vec3 pos;

    bool reached = false;
    bool failed = false;

    unsigned int steps_taken = 0;

    Rocket(DNA<Vec3> dna);
    ~Rocket();

    void run(Vec3 target, unsigned int current_dna);
    float fitness_calculate(Vec3 target);


    friend ostream& operator<< (ostream & out, const Rocket &data);
};
