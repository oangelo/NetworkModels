#ifndef SOLICITATION_MODEL_H 
#define SOLICITATION_MODEL_H 

#include <iostream>
#include <vector>
#include <random>

#include "statistics/histogram.h" 
#include "statistics/statistics.h" 


class Host{
    public:
        Host();
        Host& operator++();
        operator unsigned();
    private:
        unsigned connections;
};

std::vector<Host> PreferentialAttachment(unsigned size, unsigned amount_of_advertisers, double advertiser_probability_success);

#endif /* SOLICITATION_MODEL_H */
