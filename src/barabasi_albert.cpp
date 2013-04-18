#include "barabasi_albert.h"

std::random_device random_dev;
std::mt19937 randon_generator(random_dev());

bool Attachment(Host& host, double probability) {
    std::uniform_real_distribution<> dis(0, 1);
    if(dis(randon_generator) < probability){
        ++host;
        return true;
    }
    return false;
}

std::vector<Host> PreferentialAttachment(unsigned size) {
    Host host;
    ++host;
    unsigned initial_population = 0.1 * size;
    unsigned connections = 5;
    std::vector<Host> population(initial_population, host);

    unsigned successful_connections = 10;
    for (size_t i = 0; i < size - initial_population; ++i)
    {
        population.push_back(host);

        for (size_t j = 0; j < connections; ++j) {
            bool attach = false;
            while(!attach) {
                std::uniform_real_distribution<> dis(0, i + connections);
                unsigned item(dis(randon_generator));
                double propability(static_cast<double>(population[item]) / successful_connections);
                //std::cout << "propability " <<  propability << std::endl;
                attach = Attachment(population[item], propability);
                if(attach)
                    ++successful_connections;
            }
        }
    }
    for (auto& item: population)
        std::cout << item << std::endl;
    return population;
}
