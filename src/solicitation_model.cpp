#include "solicitation_model.h"

Host::Host(): connections(0) {
}

Host& Host::operator++() {
    ++connections;
    return *this;
}

Host::operator unsigned() {
    return connections;
}


void advertise(){

}

unsigned MaxConnections(std::vector<Host> population){
    unsigned max_connections = 0;
    for (size_t i = 0; i < population.size(); ++i)
        if(population[i] > max_connections)
            max_connections = population[i];
    return max_connections;

}

std::random_device random_dev;
std::mt19937 generator(random_dev());

std::vector<Host> PreferentialAttachment(unsigned size, unsigned amount_of_advertisers = 40, double advertiser_probability_success = 0.05) {
    Host host;
    ++host;
    unsigned connections = 4;
    std::vector<Host> population(200 * connections, host);

    std::vector<size_t> advertiser;

    unsigned time_for_new_advertiser = size / (2 * amount_of_advertisers);
    for(size_t i = 0; i < size; ++i)
    {
        std::cerr << i << std::endl;
        population.push_back(host);
        for (size_t j = 0; j < connections; ++j) {
            Histogram probability(population.size(), 0, population.size());
            for (size_t k = 0; k < population.size(); ++k)
                probability.set_bin_value(k, population[k]);
            ++(population[RandomGenerator(probability)]);
        }
        //advertisers
        std::uniform_real_distribution<> dis(0, 1);
        if(i % time_for_new_advertiser == 0) {
            Histogram probability(population.size(), 0, population.size());
            for (size_t k = 0; k < population.size(); ++k)
                probability.set_bin_value(k, population[k]);
            if(dis(generator) < 0.5)
                advertiser.push_back(RandomGenerator(probability));
        }
        for(auto& item: advertiser) {
            if(dis(generator) < advertiser_probability_success)
                ++(population[item]);
        }
    }

    Histogram histogram(MaxConnections(population), 1, MaxConnections(population));
    for (size_t j = 0; j < size; ++j) {
        histogram(population[j]);
        //std::cout << population[i] << std::endl;
    }
    std::cout << histogram << std::endl;
    return population;
}
