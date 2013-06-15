#include "barabasi_albert.h"
#include "statistics/src/statistics.h"

BarabasiAlbert::BarabasiAlbert(unsigned size,  unsigned connections, unsigned initial_population)
:Network(2), random_dev(), random_generator(random_dev())
{
    //init the network
    CreateEdge(&operator[](0), &operator[](0));
    for (size_t i = 2; i < initial_population - 2; ++i) {
        NewVertex();
        CreateEdge(&(*this)[i], &(*this)[i - 1]);
    }
    for (size_t i = 1; i < size - initial_population; ++i) {
        PreferentialAttachment(connections);
    }
}

void BarabasiAlbert::PreferentialAttachment(unsigned connections){
    using pstatistics::frequency;
    std::vector<frequency> value_frequency;
    for (size_t j(0); j < this->size(); ++j) {
        value_frequency.push_back(frequency(j, (*this)[j].size())); 
    }
    for (size_t j(0); j < connections; ++j) {
        unsigned prefered_vertex(pstatistics::RandomGenerator(value_frequency));
        NewVertex();
        CreateEdge(&(*this)[this->size() - 1], &(*this)[prefered_vertex]);
    }
}
