#ifndef BARABASI_ALBERT_H
#define BARABASI_ALBERT_H

#include <iostream>
#include <vector>
#include <random>

#include "network.h" 

namespace network_models{

  template<typename Node>
  class BarabasiAlbert: public Network<Node>{
    public:
      BarabasiAlbert(unsigned size, unsigned connections, unsigned initial_population);
    private:
      std::random_device random_dev;
      std::mt19937 random_generator;
      void PreferentialAttachment(unsigned connections, Vertex& vertex);
      std::vector<Vertex*> frequency;
  };

  template<typename Node>
  BarabasiAlbert<Node>::BarabasiAlbert(unsigned size,  unsigned connections, unsigned initial_population)
    :Network<Node>(0, "barabasi-albert"), random_dev(), random_generator(random_dev()), frequency()
  {
    //init the network
    Vertex *aux_vertex(this->NewVertex());
    for (size_t i = 0; i < initial_population; ++i) {
      Vertex *new_vertex(this->NewVertex());
      this->CreateUndirectedEdge(aux_vertex, new_vertex);
      frequency.push_back(aux_vertex); 
      frequency.push_back(new_vertex); 
      aux_vertex = new_vertex;
    }
    for (size_t i = 0; i < size - initial_population; ++i) {
      Vertex* new_vertex(this->NewVertex());
      PreferentialAttachment(connections, *new_vertex);
    }
  }

  template<typename Node>
  void BarabasiAlbert<Node>::PreferentialAttachment(unsigned connections, Vertex& vertex){
    std::uniform_real_distribution<> dist(0, frequency.size() - 1);
    for (size_t j(0); j < connections; ++j) {
      Vertex* prefered_vertex(frequency[dist(random_generator)]);
      this->CreateUndirectedEdge(prefered_vertex, &vertex);
      frequency.push_back(prefered_vertex); 
      frequency.push_back(&vertex); 
    }
  }
}
#endif /* BARABASI_ALBERT_H */
