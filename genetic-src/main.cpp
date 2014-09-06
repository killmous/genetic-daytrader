#include <cstdio>
#include <string>
#include "database.h"
#include "ga.h"

using namespace std;

//Little endian
bool bitAt(int offset, Chromosome chromo) {
    return (chromo >> offset) & 0b1;
}

bool* bitArray(int entropy, Chromosome chromo) {
    bool* ret = new bool[entropy];
    for(int i = 0; i < entropy; ++i) {
        ret[i] = bitAt(i, chromo);
    }
    return ret;
}

int iterations = 1000;
int popSize = 60;
int entropy = 14;

Database* db;

double fitness(Chromosome chromo);
double backtest(int money, bool buyBTC, bool buyLTC, bool buyDOGE, int freq, bool isExpMA, int shortPeriod, int longPeriod, int trailingStop);

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Incorrect usage\n");
        exit(1);
    }

    db = new Database(argv[1]);
    printf("%s\n", db->query("SELECT * FROM btc")[0][3].c_str());

    Population pop(popSize, entropy, 0.001, 0.1, fitness);
    pop.run(iterations, true);

    //fitness(0b11010101101010);

    delete db;

    return 0;
}

double fitness(Chromosome chromo) {
    int money = 30;
    bool* bitstring = bitArray(entropy, chromo);

    bool buyBTC  = bitstring[13];
    bool buyLTC  = bitstring[12];
    bool buyDOGE = bitstring[11];

    int freq;
    switch(bitstring[10] * 4 + bitstring[9] * 2 + bitstring[8]) {
    case 1:
        freq = 1;
        break;
    case 2:
        freq = 5;
        break;
    case 3:
        freq = 15;
        break;
    case 4:
        freq = 30;
        break;
    case 5:
        freq = 60;
        break;
    case 6:
        freq = 120;
        break;
    case 7:
        freq = 300;
        break;
    case 0:
        freq = 14400;
        break;
    }

    bool isExpMA = bitstring[7];
    int shortPeriod = 5 * (bitstring[6] * 2 + bitstring[5]) + 5;
    int longPeriod = 10 * (bitstring[4] * 2 + bitstring[3]) + 30;

    int trailingStop = bitstring[2] * 4 + bitstring[1] * 2 + bitstring[0];
    if(trailingStop == 0) trailingStop = 8;

    delete[] bitstring;

    return backtest(money, buyBTC, buyLTC, buyDOGE, freq, isExpMA, shortPeriod, longPeriod, trailingStop);
}

double backtest(int money, bool buyBTC, bool buyLTC, bool buyDOGE, int freq, bool isExpMA, int shortPeriod, int longPeriod, int trailingStop) {
    return 1.0/pow(abs(freq - 17) + 1, 2);
}