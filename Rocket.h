#pragma once

#include "include/Vec3.h"
#include "include/Citizen.hpp"
#include "include/DNA.hpp"

class Rocket : public Citizen<Vec3> {
public:
    bool reached = false;
    bool failed = false;

    unsigned int steps_taken = 0;

    Rocket(DNA<Vec3> dna);
	Rocket(DNA<Vec3> dna, Vec3 start_pos);
    ~Rocket();

    void run(Vec3 target, unsigned int current_dna);
    float fitness_calculate(Vec3 target);


    friend ostream& operator<< (ostream & out, const Rocket &data);
};
