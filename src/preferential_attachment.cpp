#include "preferential_attachment.h"

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
    std::uniform_real_distribution<> dis(0, probability);
    if(dis(gen) < probability){
        ++host;
        return true;
    }
    return false;
}

std::vector<Host> PreferentialAttachment(unsigned size, unsigned bins, double max) {
    std::vector<Host> population;
    for (size_t i = 0; i < size; ++i)
    {
        Host host;
        ++host;
        population.push_back(host);

        bool attach = false;
        while(!attach) {
            std::uniform_real_distribution<> dis(0, i + 1);
            unsigned item(dis(gen));
            double propability(static_cast<double>(population[item]) / (i + 1));
            //std::cout << "propability " <<  propability << std::endl;
            attach = Attachment(population[item], propability);
        }
    }
    Histogram histogram(bins, 0, max);
    for (size_t i = 0; i < size; ++i)
        histogram(population[i]);
    std::cout << histogram << std::endl;
    return population;
}
