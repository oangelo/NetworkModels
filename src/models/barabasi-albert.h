#ifndef BARABASI_ALBERT_H
#define BARABASI_ALBERT_H

#include <iostream>
#include <vector>
#include <random>

#include "../network.h" 

namespace network_models{

  template<typename Node>
  class BarabasiAlbert: public Network<Node>{
    public:
      BarabasiAlbert(unsigned size, double connections, unsigned initial_population = 5);
    private:
      std::random_device random_dev;
      std::mt19937 random_generator;
      void PreferentialAttachment(unsigned connections, Vertex& vertex);
      std::vector<Vertex*> frequency;
  };

  template<typename Node>
  BarabasiAlbert<Node>::BarabasiAlbert(unsigned size,  double connections, unsigned initial_population)
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
    //Dealing if halfintegers connections
    int frac_part(static_cast<int>(modf(connections, &connections)*10));
    if(frac_part == 5){
      for (size_t i = 0; i < size - initial_population - 1; ++i) {
        Vertex* new_vertex(this->NewVertex());
        if(i % 2){
          PreferentialAttachment(connections + 1, *new_vertex);
        }else{
          PreferentialAttachment(connections, *new_vertex);
        }
      }
    }else if(frac_part == 0){
      for (size_t i = 0; i < size - initial_population - 1; ++i) {
        Vertex* new_vertex(this->NewVertex());
        PreferentialAttachment(connections, *new_vertex);
      }
    }else{
      throw std::invalid_argument("The number of connections must be a interger or a half interger");
    }
  }

  template<typename Node>
    void BarabasiAlbert<Node>::PreferentialAttachment(unsigned connections, Vertex& vertex){
      unsigned max_trials(10*connections);
      std::uniform_real_distribution<> dist(0, frequency.size() - 1);
      unsigned count(0), links(0);
      while(links < connections and count < max_trials) {
        ++count;
        Vertex* prefered_vertex(frequency[dist(random_generator)]);
        try{
          this->CreateUndirectedEdge(prefered_vertex, &vertex);
          frequency.push_back(prefered_vertex); 
          frequency.push_back(&vertex); 
          ++links;
        }catch(std::invalid_argument& e){
          continue;
        }
      }
      if(count == max_trials)
          throw std::range_error("Maximum iterations reached, could not generate Barabasi-Albert network.");
    }
}
#endif /* BARABASI_ALBERT_H */
