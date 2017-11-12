#pragma once

#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <iostream>

using namespace std;

template <class T>
class DNA {
private:
    vector<T> genes;
    float fitness;
public:
    DNA(uint64_t size) {

    }

    DNA() {

    }

    DNA(const DNA<T> *genes) {
        for (auto m : genes) {
            this.gene_add(m);
        }
    }

    ~DNA() {
        cout << "Deconstructor DNA called" << endl;
    }

    DNA<T> crossover(DNA<T> *other) {
        uint64_t size_self = this->gene_size();
        uint64_t size_other = other->gene_size();
        DNA<T> new_dna;

        // Decide on the smallest size we're going to use for both vectors.
        // This ensures that we don't go over the limits of a vector.
        uint64_t size_to_use;
        if (size_self > size_other) {
            size_to_use = size_other;
        } else {
            size_to_use = size_self;
        }

        // Find a midpoint that fits within the smallest size of the vectors.
        uint64_t midpoint = (rand() % size_to_use);
        // Sometimes we pick from this first, sometimes we pick from other first
        bool order = rand() % 2;

        // From 0 to midpoint, pick a gene.
        for (size_t i = 0; i < midpoint; i++) {
            if (order) {
                new_dna.gene_add(this->genes.at(i));
            } else {
                new_dna.gene_add(other->genes.at(i));
            }

        }
        // From midpoint to the smallest vector size, pick the others
        // TODO: This is imperfect as it leaves out a possible chunk of values.
        for (size_t i = midpoint; i < size_to_use; i++) {
            if (order) {
                new_dna.gene_add(other->genes.at(i));
            } else {
                new_dna.gene_add(this->genes.at(i));
            }
        }
        return new_dna;
    }

    void mutate(float mutation_rate, vector<T> random_values) {
        for (size_t i = 0; i < genes.size(); i++) {
            float random = (rand() / (float)RAND_MAX);
            if (random < mutation_rate) {
                genes.at(i) = random_values.at(rand() % random_values.size());
            }
        }
    }

    void gene_add(T gene) {
        genes.push_back(gene);
    }

    uint64_t gene_size() {
        return genes.size();
    }

    void print() {
        cout << "DNA consisting of the following genes." << endl;
        size_t i = 0;
        for (auto &g : genes) {
            cout << g << "\t";
            i++;
            if (i == 10) {
                i = 0;
                cout << endl;
            }
        }
        cout << endl;
        cout << "End of DNA" << endl;
    }

    bool operator==(const DNA<T> &other) const {
        return this->genes == other.genes;
    }

};
