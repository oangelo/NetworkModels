#include "barabasi-albert.h"

BarabasiAlbert::BarabasiAlbert(unsigned size,  unsigned connections, unsigned initial_population)
:Network(0, "barabasi-albert"), random_dev(), random_generator(random_dev()), frequency()
{
    //init the network
    Network& network(*this);
    Vertex *aux_vertex(NewVertex());
    for (size_t i = 0; i < initial_population; ++i) {
        Vertex *new_vertex(NewVertex());
        this->CreateEdge(aux_vertex, new_vertex);
        frequency.push_back(aux_vertex); 
        frequency.push_back(new_vertex); 
        aux_vertex = new_vertex;
    }
    for (size_t i = 0; i < size - initial_population; ++i) {
        Vertex* new_vertex(NewVertex());
        PreferentialAttachment(connections, *new_vertex);
    }
}

void BarabasiAlbert::PreferentialAttachment(unsigned connections, Vertex& vertex){
    Network& network(*this);
    std::uniform_real_distribution<> dist(0, frequency.size() - 1);
    for (size_t j(0); j < connections; ++j) {
        Vertex* prefered_vertex(frequency[dist(random_generator)]);
        this->CreateEdge(prefered_vertex, &vertex);
        frequency.push_back(prefered_vertex); 
        frequency.push_back(&vertex); 
    }
}
