#include "eigenvector_centrality.h"

namespace network_models{
  Eigen::MatrixXd EigenVectorCentrality::Adjacency(Network& network){
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

  EigenVectorCentrality::EigenVectorCentrality(Network& network):map()
  {
    Eigen::MatrixXd A(Adjacency(network));
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(A);
    if (eigensolver.info() != Eigen::Success) abort();
    Eigen::VectorXd v(eigensolver.eigenvectors().col(network.size() -1));
    for(size_t i(0); i < network.size(); ++i){
      map[&network[i]] = fabs(v(i));
    }
  }

  double EigenVectorCentrality::GetMeasure(Vertex* v){
    return map[v];
  }
}
