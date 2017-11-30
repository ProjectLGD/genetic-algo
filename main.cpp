#define EXIT_OK 0
#define EXIT_ERR 1

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "include/DNA.hpp"
#include "include/Population.hpp"
#include "include/Vec3.h"

using namespace std;

vector<DNA<Vec3>> generate_data(uint64_t vector_size, uint64_t dna_size) {
    vector<DNA<Vec3>> vec;
    for (size_t i = 0; i < vector_size; i++) {
        DNA<Vec3> dna;
        for (size_t j = 0; j < dna_size; j++) {
            int x = rand()%(1024*10);
            int y = 0;
            // int y = rand()%(1024*10);
            int z = 0;
            dna.gene_add(Vec3(x, y, z));
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

    Population<Vec3> pop(Vec3(500,0,0), 0.001f, size, generate_data);
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
