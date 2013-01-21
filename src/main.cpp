#include <iostream>

#include <cstdio>

#include "barabasi_albert.h"

int main(int argc, char *argv[])
{
    unsigned population = atoi(argv[1]);
    unsigned bins = atoi(argv[2]);
    double max = atoi(argv[3]);
    PreferentialAttachment(population, bins, max);
    return EXIT_SUCCESS;
}

