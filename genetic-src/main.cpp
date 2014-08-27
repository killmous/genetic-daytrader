#include <cstdio>
#include <string>
#include "sqlite3.h"
#include "ga.h"

using namespace std;

bool bitAt(int offset, Chromosome chromo) {
    return (chromo >> (offset - 1)) & 0b1;
}

int iterations = 1000;
int popSize = 300;
int entropy = 8;

double fitness(Chromosome chromo) {
    return 1.0/(abs(chromo - 69) + 1);
}

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Incorrect usage\n");
        exit(1);
    }
    string str(argv[1]);
    sqlite3 *db;
    char *zErrMsg = nullptr;
    int rc;

    rc = sqlite3_open(str.c_str(), &db);

    sqlite3_close(db);

    Population pop(popSize, entropy, 0.001, 0.1, fitness);
    pop.run(iterations);
    return 0;
}