#include <cstdio>
#include "sqlite3.h"
#include "ga.h"

bool bitAt(int offset, Chromosome chromo) {
    return (chromo >> (offset - 1)) & 0b1;
}

int iterations = 10;
int popSize = 10;
int entropy = 8;

double fitness(Chromosome chromo) {
    return 1.0/(abs(chromo - 17) + 1);
}

int main(int argc, char **argv) {
    sqlite3 *db;
    char *zErrMsg = nullptr;
    int rc;

    rc = sqlite3_open("test.db", &db);

    if(rc) {
        printf("Error opening test.db\n");
    }

    Population pop(popSize, entropy, 0.001, 0.1, fitness);
    pop.run(iterations, true);
    return 0;
}