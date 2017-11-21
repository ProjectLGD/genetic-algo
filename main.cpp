#define EXIT_OK 0
#define EXIT_ERR 1

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "include/DNA.hpp"
#include "include/Population.hpp"

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
    srand((unsigned)time(nullptr));
    uint64_t size = 100;

    unsigned int to_run = 10000;

    cout << boolalpha; // remember this one

    cout << "How often should we run?" << endl;
    // cin >> to_run;

    Population<int> pop(500, 0.001f, size, generate_data);
    cout << "Iterating "<< to_run <<" times to evolve population" << endl;
    //char temp;
    for (size_t count = 1; count <= to_run; count++) {
        cout << "\r";
        cout << "Population " << count << flush;
        // cout << "Population " << count << endl;
        pop.natural_selection();
        pop.generate();
        // print all DNA
        // for (size_t i = 0; i < pop.popu.size(); i++) {
        //     DNA<int> *dna = &pop.popu.at(i);
        //     dna->print();
        // }
        // pop.compute_most_fit().print();
        // cin >> temp;
    }
    cout << endl;

    pop.compute_most_fit().print();

    pop.print();

    return EXIT_OK;
}
