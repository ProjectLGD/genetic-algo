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
        DNA<T> result;
        for (auto m : genes) {
            result.gene_add(m);
        }
        return result;
    }

    ~DNA() {
        cout << "Deconstructor DNA called" << endl;
    }

    DNA<T> crossover(DNA<T> *other) {
        uint64_t size_self = this->gene_size();
        uint64_t size_other = other->gene_size();
        DNA<T> new_dna;

        uint64_t size_to_use;
        if (size_self > size_other) {
            size_to_use = size_other;
        } else {
            size_to_use = size_self;
        }

        uint64_t midpoint = (rand() % size_to_use);
        bool first = rand() % 2;
        for (size_t i = 0; i < midpoint; i++) {
            if (first) {
                new_dna.gene_add(this->genes.at(i));
            } else {
                new_dna.gene_add(other->genes.at(i));
            }

        }
        for (size_t i = midpoint; i < size_to_use; i++) {
            if (first) {
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
