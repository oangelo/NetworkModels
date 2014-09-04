#ifndef CONFIGURATIONAL_H
#define CONFIGURATIONAL_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "../network.h" 

namespace network_models{

  template<typename Node>
    class Configurational: public Network<Node>{
      public:
        Configurational(std::vector<unsigned> distribution, unsigned threshold = 10);
      private:
        std::deque<Vertex*> nodes;
        std::random_device random_dev;
        std::mt19937 random_generator;
    };

  template<typename Node>
    Configurational<Node>::Configurational(std::vector<unsigned> distribution, unsigned threshold)
    :Network<Node>(distribution.size(), "Configurational Model"), nodes(),
    random_dev(), random_generator(random_dev()) {
      Network<Node>& network(*this);

      std::sort(distribution.begin(), distribution.end());
      unsigned counter(0);
      for(unsigned i(0); i < distribution.size() - 1; ++i){
        for(unsigned j(0); j < distribution[i]; ++j){
          nodes.push_back(&network[counter]);
        }
        ++counter;
      }
      std::shuffle(nodes.begin(), nodes.end(), random_generator);
      for(unsigned j(0); j < distribution.back(); ++j){
        nodes.push_back(&network[counter]);
      }

      double initial_size(nodes.size());
      unsigned iterations(0);
      while(nodes.size() > 1){
        if(nodes.front() != nodes.back()){
          try{
            this->CreateUndirectedEdge(nodes.front(), nodes.back());
            nodes.pop_front();
            nodes.pop_back();
          }catch(std::invalid_argument& e){
            nodes.push_back(nodes.front());
            nodes.pop_front();
          }
        }else{
          nodes.push_back(nodes.front());
          nodes.pop_front();
        }
        ++iterations;
        if(iterations % static_cast<unsigned>(initial_size) == 0){
          std::shuffle(nodes.begin(), nodes.end(), random_generator);
        }
        if(iterations % static_cast<unsigned>(initial_size / 100) == 0)
          std::cerr << "\% of Nodes created " <<  static_cast<int>(100 * (1 - nodes.size() / initial_size)) << "\r";
        if(iterations > threshold * initial_size){
          throw std::range_error("Too many iterations on the configurational model.");
          break;
        }
      }
    }

  std::vector<unsigned> PowerLaw(double exponent, unsigned samples, unsigned min, unsigned max);

} //namespace

#endif /* CONFIGURATIONAL_H */
