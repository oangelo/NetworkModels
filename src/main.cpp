#include <iostream>

#include <cstdio>

#include "solicitation_model.h"

int main(int argc, char *argv[])
{
    unsigned population = atoi(argv[1]);
    unsigned advertisers_amount = atoi(argv[2]);
    double probability_of_success = atof(argv[3]);
    PreferentialAttachment(population, advertisers_amount, probability_of_success);
    return EXIT_SUCCESS;
}

