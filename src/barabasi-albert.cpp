#include "barabasi-albert.h"

BarabasiAlbert::BarabasiAlbert(unsigned size,  unsigned connections, unsigned initial_population)
:Network(0, "barabasi-albert"), random_dev(), random_generator(random_dev())
{
    //init the network
    Network& network(*this);
    Vertex *aux_vertex(NewVertex());
    for (size_t i = 0; i < initial_population - 2; ++i) {
        Vertex *new_vertex(NewVertex());
        this->CreateEdge(aux_vertex, new_vertex);
        aux_vertex = new_vertex;
    }
    for (size_t i = 0; i < size - initial_population; ++i) {
        Vertex* new_vertex(NewVertex());
        PreferentialAttachment(connections, *new_vertex);
    }
}

void BarabasiAlbert::PreferentialAttachment(unsigned connections, Vertex& vertex){
    std::vector<Vertex*> frequency;
    Network& network(*this);
    for (size_t j(0); j < network.size(); ++j) {
      if(&network[j] != &vertex)
        for (size_t i(0); i < network[j].size(); ++i) 
          frequency.push_back(&network[j]); 
    }
    std::uniform_real_distribution<> dist(0, frequency.size() - 1);
    for (size_t j(0); j < connections; ++j) {
        Vertex* prefered_vertex(frequency[dist(random_generator)]);
        this->CreateEdge(prefered_vertex, &vertex);
    }
}
