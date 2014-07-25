#ifndef EIGENVECTOR_CENTRALITY_H
#define EIGENVECTOR_CENTRALITY_H 

#include <unordered_map>
#include <iostream>

#include <eigen3/Eigen/Dense>

#include "../network.h"

namespace network_models{
  class EigenVectorCentrality{
    public:
      EigenVectorCentrality(Network& network);
      double GetMeasure(Vertex* v);
    private:
      Eigen::MatrixXd Adjacency(Network& network);
      typedef std::unordered_map<Vertex*, double> VertexMeasureMap;
      VertexMeasureMap map;
  };
}
#endif /* EIGENVECTOR_CENTRALITY_H */
