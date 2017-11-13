#define EXIT_OK 0
#define EXIT_ERR 1

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "classes/DNA.hpp"

using namespace std;

int main(int argc, char** argv) {
    srand (time(NULL));
    cout << rand() % 2 << endl;
    uint64_t size = 100;
    DNA<int> dna;
    DNA<int> dna2;
    vector<int> random_values;
    // generate random dna here, because we know what type it is here.
    for (size_t i = 0; i < size; i++) {
        dna.gene_add(rand() % 1024);
        dna2.gene_add(rand() % 129);
        random_values.push_back(rand() % 13113);
    }

    dna.print();
    cout << "Current fitness is " << dna.fitness_get() << endl;
    cout << "Calculating new fitness" << endl;
    dna.fitness_calculate(500);
    cout << "New fitness is " << dna.fitness_get() << endl;



    // dna2.print();

    // DNA<int> dna3 = dna.crossover(&dna2);
    // DNA<int> dna4(dna3); //copy

    // dna3.print();
    // dna4.print();

    // cout << "Dna comparison 3-4: " << ((dna3 == dna4) ? "True" : "False") << endl;

    // dna3.mutate(0.1, random_values); // change values according to random_values
    // dna3.print();

    // cout << "Dna comparison 3-4: " << ((dna3 == dna4) ? "True" : "False") << endl;
    return EXIT_OK;
}
