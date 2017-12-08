#define EXIT_OK 0
#define EXIT_ERR 1

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "include/DNA.hpp"
#include "include/Population.hpp"
#include "include/Vec3.h"
#include "include/Rocket.h"

using namespace std;

unsigned int max_x = 10;
unsigned int max_y = 10;

vector<Rocket> generate_data(uint64_t vector_size, uint64_t dna_size) {
    vector<Rocket> vec;
    for (size_t i = 0; i < vector_size; i++) {
        DNA<Vec3> dna;
        for (size_t j = 0; j < dna_size; j++) {
            int x = rand() % (max_x*2) - max_x; // also generate negative numbers.
            int y = rand() % (max_x*2) - max_x;
            // int y = 0;
            int z = 0;
            dna.gene_add(Vec3(x, y, z));
        }
        // add this to a citizen.
        Rocket cit(dna);
        vec.push_back(cit);
    }

    return vec;
}

int main(int argc, char** argv) {
    (void) argc; // unused
    (void) argv; // unused
    cout << endl;
    srand((unsigned)time(nullptr));

    uint64_t size = 25;
    uint64_t dna_size = 500;

    unsigned int to_run = 10000;

    cout << boolalpha; // remember this one

    // Vec3 v;
    // cout << v << endl;
    // Vec3 v2(1, 2, 3);
    // cout << v2 << endl;
    // Vec3 v3(3, 2, 1);
    // cout << v3 << endl;
    // cout << "Adding" << endl;
    // cout << (v3 + v2) << endl;

    cout << "How often should we run?" << endl;
    // cin >> to_run;

    Vec3 tgt(100, 200, 0);

    Population<Vec3, Rocket> pop(tgt, 0.01f, size, dna_size, generate_data);
    cout << "Iterating "<< to_run <<" times to evolve population" << endl;
    char temp;

    for (size_t count = 1; count <= to_run; count++) {
        cout << "\r";
        cout << "Population " << count << flush;
        // cout << "Population " << count << endl;
        pop.fitness_calculate();
        pop.natural_selection();
        pop.compute_most_fit();
        pop.generate();
        cin >> temp;
    }
    cout << endl;

    return EXIT_OK;
}
