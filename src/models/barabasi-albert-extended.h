#ifndef BARABASI_ALBERT_EXTENDED_H
#define BARABASI_ALBERT_EXTENDED_H

#include <iostream>
#include <vector>
#include <random>
#include <exception>
#include <set>
#include <iterator>

#include "../network.h" 

namespace network_models{

  template<typename Node>
  class BarabasiAlbertExtended: public Network<Node>{
    public:
      BarabasiAlbertExtended(unsigned size, unsigned m0, unsigned m, double p, double q);
    private:
      std::random_device random_dev;
      std::mt19937 random_generator;
      void PreferentialAttachment(unsigned connections, Vertex& vertex);

      void AddNode(unsigned m);
      void AddLink(unsigned m);
      void Rewire(unsigned m);
      std::multiset<Vertex*> frequency;
  };

  template<typename Node>
    BarabasiAlbertExtended<Node>::BarabasiAlbertExtended(unsigned size, unsigned m0, unsigned m,
        double r, double l)
    :Network<Node>(0, "barabasi-albert-extended"), random_dev(), random_generator(random_dev()), frequency() 
    {
      if(r + l >= 1)
        throw std::invalid_argument(
            "The parameter should be r + l < 1 on the Extended Barabasi-Albert model!");
      for (size_t i = 0; i < m; ++i) 
        frequency.insert(this->NewVertex());

      std::uniform_real_distribution<> dis(0, 1);
      while(this->size() < size){
        double rn(dis(random_generator));
        if(rn < r){
          this->Rewire(m);
        }else if(rn < r + l){
          this->AddLink(m);
        }else{
          this->AddNode(m);
        }
      }
    }

  template<typename Node>
  void BarabasiAlbertExtended<Node>::AddLink(unsigned m){
      Network<Node>& network(*this);
      std::uniform_int_distribution<> dist(0, network.size() - 1);
      for (size_t i = 0; i < m; ++i) {
        Vertex* target(&network[dist(random_generator)]);
        PreferentialAttachment(1, *target);
      }
    }

  template<typename Node>
    void BarabasiAlbertExtended<Node>::AddNode(unsigned m){
      Vertex* target(this->NewVertex());
      frequency.insert(target);
      PreferentialAttachment(m, *target);
    }

  template<typename Node>
  void BarabasiAlbertExtended<Node>::Rewire(unsigned m){
      Network<Node>& network(*this);
      std::uniform_int_distribution<> dist(0, network.size() - 1);
      for (size_t i = 0; i < m; ++i) {
        Vertex& target(network[dist(random_generator)]);
        if(target.size() > 0){
          std::uniform_int_distribution<> rd_edges(0, target.size() - 1);
          Edge& edge(target(rd_edges(random_generator)));
          auto it_target(frequency.find(&target));
          if(it_target == frequency.end()){
            throw std::invalid_argument("bad target");
          }else{
            frequency.erase(it_target);
          }
          auto it_to(frequency.find(edge.To()));
          if(it_to == frequency.end()){
            throw std::invalid_argument("bad to");
          }else{
            frequency.erase(it_to);
          }
          Vertex* to(edge.To());
 //         std::cout << "removing from target " << target.size() << std::endl;
          target.Remove(*to);
//          std::cout << "removing from to" << std::endl;
          to->Remove(target);
          //this->RemoveUndirectedEdge(edge.From(), edge.To());
          PreferentialAttachment(1, target);
        }
      }
    }

  template<typename Node>
    void BarabasiAlbertExtended<Node>::PreferentialAttachment(unsigned connections, Vertex& vertex){
      std::uniform_int_distribution<> dist(0, frequency.size() - 1);
      for (size_t j(0); j < connections; ++j) {
        auto it(frequency.begin());
        std::advance(it, dist(random_generator));
        Vertex* prefered_vertex(*it);
        try{
          this->CreateUndirectedEdge(prefered_vertex, &vertex);
          frequency.insert(prefered_vertex); 
          frequency.insert(&vertex); 
        }catch(std::invalid_argument& e){
          continue;
        }
      }
    }
}

#endif /* BARABASI_ALBERT_EXTENDED_H */
