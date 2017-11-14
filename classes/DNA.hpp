#pragma once

#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <iostream>
#include <limits>

using namespace std;

template <class T>
class DNA {
private:
    // The genes of this DNA. Can contain any object.
    vector<T> genes;

    // The fitness of this particular DNA.
    // Will only be accurate after calling the fitness function.
    float fitness = 0.0f;

public:

    DNA() {

    }

    DNA(const DNA<T> *genes) {
        for (auto m : genes) {
            gene_add(m);
        }
    }

    ~DNA() {
        cout << "Deconstructor DNA called" << endl;
    }

    // Crosses two DNA's into a new one.
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

    // Mutates the genes using mutation_rate with values provided by random_values.
    void mutate(float mutation_rate, vector<T> random_values) {
        for (size_t i = 0; i < genes.size(); i++) {
            float random = (rand() / (float)RAND_MAX);
            if (random < mutation_rate) {
                genes.at(i) = random_values.at(rand() % random_values.size());
            }
        }
    }

    // Calculates the fitness for this particular DNA.
    void fitness_calculate(T target) {
        float score = 0.0f;
        float distance_max = numeric_limits<float>::min();
        float distance_min = numeric_limits<float>::max();

        // TODO: Check if distance_max is needed.

        // Calculate the distance to T for every gene.
        for (size_t i = 0; i < genes.size(); i++) {
            T current = genes.at(i);
            // We can not use abs() because T is not guaranteed to be float or int etc.
            float distance_current;
            // Work around abs() not supporting much more than default datatypes.
            if (current > target) {
                distance_current = current - target;
            } else {
                distance_current = target - current;
            }
            if (distance_current > distance_max) {
                distance_max = distance_current;
            }
            if (distance_current < distance_min) {
                distance_min = distance_current;
            }
        }

        cout << "Max and min are " << distance_max << " " << distance_min << endl;

        // The worst case scenario is distance_max, the best is distance_min being 0.
        if (distance_min == 0) {
            fitness = 1.0f;
        } else {
            // The smaller distance_min, the higher the fitness should be.
            // TODO: Fix me. See ideally vs right now.
            // Ideally:
            // 1 / 0 (1.0f)
            // 1 / 1 (0.9f)
            // 1 / 2 (0.8f)

            // Right now:
            // 1 / 0 (1.0f)
            // 1 / 1 (0.5f)
            // 1 / 2 (0.25f)
            fitness = 1.0f / (distance_min * 2);
        }
    }

    float fitness_get() {
        return fitness;
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
