#pragma once

#include <iostream>

using namespace std;

// TODO: Check if I'm using size() -1 for the vectors in the rest in the file.

template <class T>
class Population {
    typedef vector<DNA<T>>(*dna_gen_func)(uint64_t vector_size, uint64_t dna_size);
private:
    T target; // our target, T. The population wants to be as close as possible to target.
    float mutation_rate; // how often mutations occur.
    uint64_t population_size; // The size of the
    vector<DNA<T>> popu; // current population filled with DNA
    vector<DNA<T>> mating_pool; // the pool used when making new generation
    bool finished = false; // not in use yet
    int perfect_score = 1; // not in use yet.
    uint64_t generation = 0; // current generation
    dna_gen_func gen_func = nullptr; // thefunction to use to generate random data, as inside this class, T is still unknown.

public:
    Population(T target, float mutation_rate, uint64_t population_size, dna_gen_func func) {

        this->target = target;
        this->mutation_rate = mutation_rate;
        this->population_size = population_size;
        this->gen_func = func;

        // fill population with DNA.
        // TODO: remove hardcoded value;
        // Generate random DNA, so we're generating 100 DNA<T>'s of size 100;
        vector<DNA<T>> random_dna = dna_generate(population_size, 10);
        for (size_t i = 0; i < random_dna.size(); i++) {
            DNA<T> dna = random_dna.at(i);
            popu.push_back(dna); // this copies the dna to popu
        }

        fitness_calculate();
    }

    Population(const Population<T> *p) {
        this->target = p->target;
        this->mutation_rate = p->mutation_rate;
        this->population_size = p->population_size;
        this->gen_func = p->gen_func;

        this->popu = p->popu;
    }

    void fitness_calculate() {
        for (size_t i = 0; i < popu.size(); i++) {
            // These have to be pointers otherwise we're not accesing the actual DNA inside the vec.
            DNA<T> *dna = &popu.at(i);
            // cout << "Dna fitness is " << dna->fitness_get();
            dna->fitness_calculate(target);
            // cout << " and now it is " << dna->fitness_get() << endl;
        }
    }

    void natural_selection() {
        mating_pool.clear();

        // Find max fitness.
        float fitness_max = 0.0f;
        for (size_t i = 0; i < popu.size(); i++) {
            DNA<T> *dna = &popu.at(i);
            // cout << "Dna fitness " << dna->fitness_get() << endl;
            if (dna->fitness_get() > fitness_max) {
                fitness_max = dna->fitness_get();
            }
        }

        // cout << "Fitness max is " << fitness_max << endl;

        for (size_t i = 0; i < popu.size(); i++) {
            DNA<T> *dna = &popu.at(i);
            float fitness_current = dna->fitness_get();
            // cout << "Current fitness " << fitness_current << endl;

            // TODO: We're assuming that fitness_max is not 0.

            // remap the current fitness on a scale of 0 to maxFitness in between 0 and 1.
            float fitness_new = (fitness_current / fitness_max);
            // cout << "New fitness " << fitness_new << endl;
            size_t size_to_copy = (size_t) (fitness_new * popu.size());
            for (size_t i = 0; i < size_to_copy; i++) {
                mating_pool.push_back(popu.at(i));
            }
        }
        // cout << "Mating pool size: " << mating_pool.size() << endl;
    }

    void generate() {
        // Refill the population with children from the mating pool.

        // This verifies we're actually replacing the value in popu.
        // popu.at(0).print();
        for (size_t i = 0; i < popu.size(); i++) {
            // Get parents
            DNA<T> partner1 = mating_pool.at(rand() % (mating_pool.size() - 1));
            DNA<T> partner2 = mating_pool.at(rand() % (mating_pool.size() - 1));

            // Make new child
            DNA<T> child = partner1.crossover(&partner2);

            // cout << "Turning partner 1 and partner 2 into child" << endl;
            // partner1.print();
            // partner2.print();
            // child.print();

            vector<T> random_values = dna_generate(1, child.gene_size()).at(0).gene_get();
            child.mutate(mutation_rate, random_values);

            // add child to population.
            popu.at(i) = child;
        }
        fitness_calculate(); // don't forget to calculate fitness so that all our new children are fit =D
        // If they're the same, that's not good.
        // popu.at(0).print();
        generation++;
    }

    DNA<T> compute_most_fit() {
        fitness_calculate();
        float fitness_max = 0.0f;
        size_t index = 0;
        for (size_t i = 0; i < popu.size(); i++) {
            DNA<T> dna = popu.at(i);
            float fitness_current = dna.fitness_get();
            // cout << "Current fitness " << fitness_current << endl;
            if (fitness_current > fitness_max) {
                fitness_max = fitness_current;
                index = i;
            }
        }
        cout << "The most fit DNA is index " << index << " with a fitness of " << fitness_max << endl;
        return popu.at(index);
    }

    vector<DNA<T>> dna_generate(uint64_t vector_amount, uint64_t dna_amount) {
        return gen_func(vector_amount, dna_amount);
    }

    void print() {
        cout << "Population consisting of the following variables" << endl;
        cout << "Target:\t\t\t" << target << endl;
        cout << "Mutation rate:\t\t" << mutation_rate << endl;
        cout << "Population size:\t" << population_size << endl;
        cout << "Generation:\t\t" << generation << endl;
        cout << "End of population" << endl;
        cout << endl;
    }

    bool operator==(const Population<T> &other) const {
        return (this->generation == other.generation) && (this->popu == other.popu);
    }
};
