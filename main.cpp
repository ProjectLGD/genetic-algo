#define EXIT_OK 0
#define EXIT_ERR 1

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "classes/DNA.hpp"
#include "classes/Population.hpp"

using namespace std;

vector<DNA<int>> generate_data(uint64_t vector_size, uint64_t dna_size) {
    vector<DNA<int>> vec;
    for (size_t i = 0; i < vector_size; i++) {
        DNA<int> dna;
        for (size_t j = 0; j < dna_size; j++) {
            dna.gene_add(rand()%(1024*10));
        }
        vec.push_back(dna);
    }

    return vec;
}

int main(int argc, char** argv) {
    cout << endl;
    srand(time(nullptr));
    uint64_t size = 100;

    cout << boolalpha; // remember this one

    Population<int> pop(500, 0.01f, size, generate_data);
    pop.print();
    Population<int> pop2(pop);
    cout << "Testing equals func of Population" << endl;
    cout << (pop == pop2) << endl;
    pop.natural_selection();
    pop.generate();
    pop.print();
    pop.compute_most_fit().print();
    cout << "Testing equals func of Population" << endl;
    cout << (pop == pop2) << endl;
    return EXIT_OK;
}
