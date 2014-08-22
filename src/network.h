#ifndef NETWORK_H
#define NETWORK_H 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>

#include "vertex.h"

namespace network_models{

  template <typename Node>
  class Network{
    public:
      typedef std::deque<Node> container;
      typedef typename container::iterator iterator;

      Node& operator[](unsigned index);
      unsigned size() const;
      iterator begin();
      iterator end();

      std::string GetModelName();
      double GetMeanConnectivity();
      virtual ~Network() = 0;
    protected:
      Network(unsigned size, std::string model_name);

      Vertex* NewVertex();
      void CreateUndirectedEdge(Vertex* v1, Vertex* v2);
      const container get_vertexes();

    private:
      container vertexes;
      std::string model_name;

      //the Network class should never be copied!
      Network& operator=(const Network& network);
      Network(const Network& network);
  };

  typedef std::pair<unsigned, unsigned> bin;
  template<typename Type>
  std::vector<bin> NodesDistribution(Network<Type>& netework);

  template<typename Type>
  void Graphviz(Network<Type>& network, std::string file_name);

  template<typename Type>
  std::map<int,std::vector<unsigned>> Clusters(Network<Type>& network);


  template <typename Node>
  Network<Node>::Network(unsigned size, std::string model_name)
    :vertexes(size), model_name(model_name){}

  template <typename Node>
  unsigned Network<Node>::size() const{
    return vertexes.size();
  }

  template <typename Node>
  typename Network<Node>::iterator Network<Node>::begin(){
    return vertexes.begin(); 
  }

  template <typename Node>
  typename Network<Node>::iterator Network<Node>::end(){
    return vertexes.end();
  }

  template <typename Node>
  Node& Network<Node>::operator[](unsigned index){
    return vertexes[index];
  }

  template <typename Node>
  const std::deque<Node> Network<Node>::get_vertexes() {
    return vertexes;
  }

  template <typename Node>
  Vertex* Network<Node>::NewVertex(){
    vertexes.push_back(Node());
    return (&vertexes.back());
  }

  template <typename Node>
  void Network<Node>::CreateUndirectedEdge(Vertex* v1, Vertex* v2) {
    v1->Add(Edge(v1, v2, true));
    v2->Add(Edge(v2, v1, true));
  }

  template <typename Node>
  std::string Network<Node>::GetModelName(){
    return model_name;
  }


  template <typename Node>
  double Network<Node>::GetMeanConnectivity(){
    unsigned sum(0);
    for(Vertex& v: vertexes)
      sum += v.size();
    return static_cast<double>(sum) / vertexes.size();
  }

  template <typename Node>
  Network<Node>::~Network(){}

  template<typename Type>
  std::vector<bin> NodesDistribution(Network<Type>& network){
    std::vector<unsigned> edge_amount; 
    std::vector<bin> result;
    for (size_t i = 0; i < network.size(); ++i) {
      edge_amount.push_back(network[i].size());
    }
    unsigned max(*std::max_element(edge_amount.begin(), edge_amount.end()));
    std::vector<unsigned> histogram(max, 0); 
    for (size_t i = 0; i < edge_amount.size(); ++i) {
      if(edge_amount[i] > 0)
        ++histogram[edge_amount[i] - 1];
    }
    for (size_t i = 0; i < histogram.size(); ++i) 
      result.push_back(bin(i+1, histogram[i]));
    return(result);
  }

  template<typename Type>
  void Graphviz(Network<Type>& network, std::string file_name){
    typedef std::pair<const Vertex*, const Vertex*> key;
    std::set<key> set;
    std::ofstream file;
    file.open(file_name);

    file << "graph G {" << std::endl;
    for (size_t i = 0; i < network.size(); ++i) {
      for (size_t j = 0; j < network[i].size(); ++j) {
        if(set.find(key(&network[i][j], &network[i][j])) == set.end()){
          file << "\"" << network[i](j).From() << "\"" << " -- " << "\"" << network[i](j).To() << "\""<< std::endl; 
          set.insert(key(network[i](j).From(), network[i](j).To()));
          set.insert(key(network[i](j).To(), network[i](j).From()));
        }
      }
    }

    file << "}" << std::endl;

    file.close();
  }

//  std::set<Vertex*> Burn(Vertex* vertex){
//    bool has_neighbors = true;
//    std::set<Vertex*> cluster;
//    std::vector<Vertex*> to_search;
//    to_search.push_back(vertex);
//    int mark = vertex->GetMark();
//    while(has_neighbors){
//      cluster.insert(to_search[to_search.size() - 1]);
//      Vertex& fire(*to_search[to_search.size() - 1]);
//      to_search.pop_back();
//      for(size_t i(0); i < fire.size(); ++i){
//        if(fire[i].GetMark() == mark && (cluster.find(&fire[i]) == cluster.end())){
//          to_search.push_back(&fire[i]);
//        }
//      }
//      if(to_search.size() == 0)
//        has_neighbors = false;
//    }
//    return cluster;
//  }


//  template<typename Type>
//  std::map<int,std::vector<unsigned>> Clusters(Network<Type>& network){
//    std::map<int, std::vector<unsigned>> size; 
//    std::set<Vertex*> burnt; 
//
//    std::set<int> mark_set;
//    for(size_t i(0); i < network.size(); ++i){ 
//      mark_set.insert(network[i].GetMark());
//    }
//    for(int i: mark_set){
//      std::vector<unsigned> aux;
//      size.insert(std::pair<int, std::vector<unsigned>>(i, aux));
//    }
//
//    for(size_t i(0); i < network.size(); ++i){ 
//      if(burnt.find(&network[i]) == burnt.end()){
//        std::set<Vertex*> cluster(Burn(&network[i])); 
//        size[network[i].GetMark()].push_back(cluster.size());
//        burnt.insert(cluster.begin(), cluster.end());
//      }
//    }
//    return(size);
//
//  }


} // namespace end
#endif /* NETWORK_H */
