#include <cstdio>
#include <string>
#include "database.h"
#include "ga.h"

using namespace std;

bool bitAt(int offset, Chromosome chromo) {
    return (chromo >> (offset - 1)) & 0b1;
}

int iterations = 10;
int popSize = 300;
int entropy = 14;

Database* db;

double fitness(Chromosome chromo) {
    return 1.0/(abs(chromo - 17) + 1);
}

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Incorrect usage\n");
        exit(1);
    }

    db = new Database(argv[1]);
    printf("%s\n", db->query("SELECT * FROM btc")[0][3].c_str());

    Population pop(popSize, entropy, 0.001, 0.1, fitness);
    pop.run(iterations, true);

    delete db;

    return 0;
}