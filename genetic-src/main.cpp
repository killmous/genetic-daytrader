#include <cstdio>
#include "sqlite3.h"
#include "ga.h"

bool bitAt(int offset, Chromosome chromo) {
    return (chromo >> (offset - 1)) & 0b1;
}

int iterations = 10000000;
int popSize = 300;
int entropy = 64;

double fitness(Chromosome chromo) {
    return 1.0/(abs(chromo - 69) + 1);
}

int main(int argc, char **argv) {
    Population pop(popSize, entropy, 0.001, 0.1, fitness);
    pop.run(iterations, true);
    return 0;
}