#ifndef EIGENVECTOR_CENTRALITY_H
#define EIGENVECTOR_CENTRALITY_H 

#include <iostream>

#include <eigen3/Eigen/Dense>

#include "../network.h"
#include "interface.h"


namespace network_models{

  class EigenVectorCentrality: public Measures{
    public:
      template<typename Node> 
      EigenVectorCentrality(Network<Node>& network);
    private:
      template<typename Node> 
      Eigen::MatrixXd Adjacency(Network<Node>& network);
  };

  template<typename Node> 
  Eigen::MatrixXd EigenVectorCentrality::Adjacency(Network<Node>& network){
    Eigen::MatrixXd m(Eigen::MatrixXd::Zero(network.size(), network.size()));
    std::unordered_map<Vertex*, unsigned> map;
    for(size_t i(0); i < network.size(); ++i){
      map[&network[i]] = i;
    }
    for(size_t i(0); i < network.size(); ++i){
      for(size_t j(0); j < network[i].size(); ++j){
        m(map[&(network[i][j])], i) = 1;
      }
    }
    return m;
  }

  template<typename Node> 
  EigenVectorCentrality::EigenVectorCentrality(Network<Node>& network): Measures()
  {
    Eigen::MatrixXd A(Adjacency(network));
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(A);
    if (eigensolver.info() != Eigen::Success) abort();
    Eigen::VectorXd v(eigensolver.eigenvectors().col(network.size() -1));
    for(size_t i(0); i < network.size(); ++i){
      map[&network[i]] = fabs(v(i));
    }
  }


}

#endif /* EIGENVECTOR_CENTRALITY_H */
