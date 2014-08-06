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

  class Network{
    public:
      typedef std::deque<Vertex> container;
      typedef container::iterator iterator;

      Vertex& operator[](unsigned index);
      unsigned size() const;
      iterator begin();
      iterator end();

      std::string GetModelName();
      double GetMeanConnectivity();
      unsigned GetKshellVertexes(Vertex& target);
      virtual ~Network() = 0;
    protected:
      Network(unsigned size, std::string model_name);

      Vertex* NewVertex();
      void CreateUndirectedEdge(Vertex* v1, Vertex* v2);
      const container get_vertexes();

    private:
      container vertexes;
      std::string model_name;

      //k-shell algorithm (ref arXiv:cs/0310049v1)
      typedef std::unordered_map<Vertex*, unsigned> shell_map;
      shell_map kshell;
      void BuildKshell();

      //the Network class should never be copied!
      Network& operator=(const Network& network);
      Network(const Network& network);
  };

  typedef std::pair<unsigned, unsigned> bin;
  std::vector<bin> NodesDistribution(Network& netework);

  void Graphviz(Network& network, std::string file_name);

  //Burn for Mark
  std::set<Vertex*> Burn(Vertex* vertex);
  std::map<int,std::vector<unsigned>> Clusters(Network& network);

} // namespace end
#endif /* NETWORK_H */
