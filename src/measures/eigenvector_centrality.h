#ifndef EIGENVECTOR_CENTRALITY_H
#define EIGENVECTOR_CENTRALITY_H 

#include <iostream>

#include <eigen3/Eigen/Dense>

#include "../network.h"
#include "interface.h"


namespace network_models{
  class EigenVectorCentrality: public Measures{
    public:
      EigenVectorCentrality(Network& network);
    private:
      Eigen::MatrixXd Adjacency(Network& network);
  };
}

#endif /* EIGENVECTOR_CENTRALITY_H */
