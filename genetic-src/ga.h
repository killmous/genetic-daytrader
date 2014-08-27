#ifndef __GA__H_
#define __GA__H_

#include <algorithm>

typedef unsigned long Chromosome;

class Population {
public:
    Population( int populationSize,
                int entropy,
                double pm,
                double pc,
                std::function<double*(Chromosome*, int)> fitnessFunc);
    Population( int populationSize,
                int entropy,
                double pm,
                double pc,
                std::function<double(Chromosome)> fitnessFunc);
    ~Population(void);

    void run(int iterations, bool debug = false);
    void print(void);
private:
    int _populationSize;
    int _entropy;
    Chromosome* _population;
    double _pmutation;
    double _pcrossover;
//    double* (*_fitnessFunc)(Chromosome*, int);
    std::function<double*(Chromosome*, int)> _fitnessFunc;

    void evolve(void);
};

Chromosome chooseWeighted(Chromosome* pop, double* fitness, int size);

#endif