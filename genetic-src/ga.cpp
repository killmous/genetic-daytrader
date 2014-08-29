#include "ga.h"
#include <ctime>


//
//Population
//

Population::Population(int populationSize,
                       int entropy,
                       double pm,
                       double pc,
                       std::function<double*(Chromosome*, int)> fitnessFunc) {
    _populationSize = populationSize;
    _entropy = entropy;
    _population = new Chromosome[_populationSize];
    _pmutation = pm;
    _pcrossover = pc;
    _fitnessFunc = fitnessFunc;

    srand(time(NULL));

    for(int i = 0; i < _populationSize; ++i) {
        _population[i] = rand() % (1 << entropy);
    }
}

Population::Population(int populationSize,
                       int entropy,
                       double pm,
                       double pc,
                       std::function<double(Chromosome)> fitnessFunc) :
    Population( populationSize,
                entropy,
                pm,
                pc,
                [=](Chromosome* pop, int popsize) -> double* {
                    double* ret = new double[popsize];
                    for(int i = 0; i < popsize; ++i) {
                        ret[i] = fitnessFunc(pop[i]);
                    }
                    return ret;
                }) {}

Population::~Population(void) {
    delete[] _population;
}

void Population::run(int iterations, bool debug) {
    printf("Initial population: ");
    this->print();
    for(int i = 0; i < iterations; ++i) {
        this->evolve();
        if(debug) this->print();
    }
    printf("Final population: ");
    this->print();
}

void Population::print(void) {
    for(int i = 0; i < _populationSize; ++i) {
        printf((i != _populationSize-1) ? "%d " : "%d", _population[i]);
    } printf("\n");
}

void Population::evolve(void) {
    double* fitness = _fitnessFunc(_population, _populationSize);

    Chromosome* intermediate = chooseWeighted(_population, fitness, _populationSize);

    for(int i = 0; i < _populationSize; ++i) {
        if(rand() <= _pcrossover * RAND_MAX && i != _populationSize - 1) {
            int crossoverPoint = rand() % (_entropy - 1);
            Chromosome cut1 = intermediate[i] & ((1 << (crossoverPoint + 1)) - 1);
            Chromosome cut2 = intermediate[i + 1] & ((1 << (crossoverPoint + 1)) - 1);
            intermediate[i] += (cut2 - cut1);
            intermediate[++i] += (cut1 - cut2);
        }

        if(rand() <= _pmutation * RAND_MAX) {
            intermediate[i] ^= (1 << (rand() % _entropy));
        }
    }

    delete[] _population;
    delete[] fitness;
    _population = intermediate;
}

Chromosome* chooseWeighted(Chromosome* pop, double* fitness, int size) {
    double sumOfWeights = 0;
    Chromosome* chromo = new Chromosome[size];
    for(int i = 0; i < size; ++i) {
        sumOfWeights += fitness[i];
    }

    for (int i = 0; i < size; ++i) {
        double rnd = (double)rand()/RAND_MAX * sumOfWeights;
        for (int j = 0; j < size; ++j) {
            if (rnd < fitness[j]) {
                chromo[i] = pop[j];
                break;
            }
            rnd -= fitness[j];
        }
    }
    return chromo;
}