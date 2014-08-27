#include <cstdio>
#include <string>
#include "database.h"
#include "ga.h"

using namespace std;

bool bitAt(int offset, Chromosome chromo) {
    return (chromo >> (offset - 1)) & 0b1;
}

static int callback(void* data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for(i=0; i<argc; i++){
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int iterations = 10;
int popSize = 300;
int entropy = 8;

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
    delete db;

    Population pop(popSize, entropy, 0.001, 0.1, fitness);
    pop.run(iterations);

    return 0;
}