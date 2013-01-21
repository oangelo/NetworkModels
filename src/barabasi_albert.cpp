#include "barabasi_albert.h"

Host::Host(): connections(0) {
}

Host& Host::operator++() {
    ++connections;
    return *this;
}

Host::operator unsigned() {
    return connections;
}

std::random_device rd;
std::mt19937 gen(rd());

bool Attachment(Host& host, double probability) {
    std::uniform_real_distribution<> dis(0, 1);
    if(dis(gen) < probability){
        ++host;
        return true;
    }
    return false;
}

std::vector<Host> PreferentialAttachment(unsigned size, unsigned bins, double max) {
    Host host;
    ++host;
    unsigned connections = 5;
    std::vector<Host> population(2 * connections, host);

    unsigned successful_connections = 10;
    for (size_t i = 0; i < size; ++i)
    {
        population.push_back(host);

        for (size_t j = 0; j < connections; ++j) {
            bool attach = false;
            while(!attach) {
                std::uniform_real_distribution<> dis(0, i + connections);
                unsigned item(dis(gen));
                double propability(static_cast<double>(population[item]) / successful_connections);
                //std::cout << "propability " <<  propability << std::endl;
                attach = Attachment(population[item], propability);
                if(attach)
                    ++successful_connections;
            }
        }
    }
    Histogram histogram(bins, 1, max);
    for (size_t i = 0; i < size; ++i)
        histogram(population[i]);
    std::cout << histogram << std::endl;
    return population;
}
