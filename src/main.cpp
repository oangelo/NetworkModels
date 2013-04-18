#include <iostream>
#include <string>

#include <cstdio>

#include "solicitation_model.h"
#include "barabasi_albert.h"

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if(std::string(argv[i]) == std::string("--solicitation-model"))
        {
            unsigned population = atoi(argv[i + 1]);
            unsigned advertisers_amount = atoi(argv[i + 2]);
            double probability_of_success = atof(argv[i + 3]);
            PreferentialAttachment(population, advertisers_amount, probability_of_success);
        }
        if(std::string(argv[i]) == std::string("--barabasi-albert"))
        {
            unsigned size = atoi(argv[i + 1]);
            PreferentialAttachment(size);
        }
    }
    return EXIT_SUCCESS;
}

