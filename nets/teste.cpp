#include <iostream>

#include <network_models/network.h>
#include <network_models/utilities.h>
#include <network_models/real-network.h>

int main(){
  using namespace network_models;
  RealUndirectedNetwork net("facebook_combined.txt");
  Graphviz(net, "net_facebook.dot");
  std::cout << IsUndirected(net.begin(), net.end()) << std::endl;
  return EXIT_SUCCESS;
}

