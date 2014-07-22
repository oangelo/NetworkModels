#include "network_models/square.h"
#include "network_models/mean-field.h"
#include "network_models/measures.h"

using namespace network_models;

//the k shell of a square network is 2 for all nodes
TEST(measures, kshellSquare){
    unsigned nodes = 100;
    Square network(nodes);
    for(size_t i(0); i < network.size(); ++i){
      unsigned rank(network.GetKshellVertexes(network[i]));
      EXPECT_EQ(rank, 2);
    }
}

TEST(measures, kshellBarabasi){
    unsigned nodes(25);
    unsigned m(8);
    BarabasiAlbert network(nodes, m, 10);
//    Graphviz(network, "kshell_BA.dot");
    std::vector<unsigned> aux;
    for(size_t i(0); i < network.size(); ++i){
      unsigned rank(network.GetKshellVertexes(network[i]));
      aux.push_back(rank);
    }
    EXPECT_TRUE(*std::max_element(aux.begin(), aux.end()) <= m);
}

TEST(measures, kshellErdos_Renyi){
    unsigned nodes(1125);
    unsigned m(8);
    ErdosRenyi network(nodes, m*nodes);
//    Graphviz(network, "kshell_ER.dot");
    std::vector<unsigned> aux;
    for(Network::iterator it(network.begin()); it < network.end(); ++it){
      unsigned rank(network.GetKshellVertexes(*it));
      aux.push_back(rank);
    }
    EXPECT_TRUE(*std::max_element(aux.begin(), aux.end()) <= 2*m);
}

//partial example(right) of reference arXiv:cs/0310049v1
TEST(measures, kshellSimpleNet){
  class NetTest: public Network{
    public:
    NetTest():Network(6, "test"){
      Network& network(*this);
      CreateEdge(&network[1], &network[2]);  
      CreateEdge(&network[2], &network[4]);  
      CreateEdge(&network[3], &network[4]);  
      CreateEdge(&network[3], &network[1]);  
      CreateEdge(&network[0], &network[1]);  
    };
  } network;
    
  EXPECT_EQ(network.GetKshellVertexes(network[0]), 1);
  EXPECT_EQ(network.GetKshellVertexes(network[1]), 2);
  EXPECT_EQ(network.GetKshellVertexes(network[2]), 2);
  EXPECT_EQ(network.GetKshellVertexes(network[3]), 2);
  EXPECT_EQ(network.GetKshellVertexes(network[4]), 2);
  EXPECT_EQ(network.GetKshellVertexes(network[5]), 0);
}

//partial example(left) of reference arXiv:cs/0310049v1
TEST(measures, kshellSimpleNet2){
  class NetTest: public Network{
    public:
    NetTest():Network(15, "test"){
      Network& network(*this);
      CreateEdge(&network[0], &network[2]);  
      CreateEdge(&network[1], &network[2]);  
      CreateEdge(&network[2], &network[3]);  
      CreateEdge(&network[2], &network[5]);  
      CreateEdge(&network[3], &network[4]);  
      CreateEdge(&network[3], &network[5]);  
      CreateEdge(&network[4], &network[8]);  
      CreateEdge(&network[4], &network[9]);  
      CreateEdge(&network[4], &network[6]);  
      CreateEdge(&network[6], &network[8]);  
      CreateEdge(&network[6], &network[9]);  
      CreateEdge(&network[8], &network[9]);  
      CreateEdge(&network[5], &network[7]);  
      CreateEdge(&network[5], &network[10]);  
      CreateEdge(&network[5], &network[11]);  
      CreateEdge(&network[7], &network[10]);  
      CreateEdge(&network[7], &network[11]);  
      CreateEdge(&network[10], &network[11]);  
      CreateEdge(&network[9], &network[10]);  
      CreateEdge(&network[9], &network[12]);  
      CreateEdge(&network[10], &network[12]);  
      CreateEdge(&network[10], &network[13]);  
      CreateEdge(&network[12], &network[13]);  
      CreateEdge(&network[12], &network[14]);  
    };
  } network;
  //Graphviz(network, "kshell_test2.dot");
  EXPECT_EQ(network.GetKshellVertexes(network[0]), 1);
  EXPECT_EQ(network.GetKshellVertexes(network[1]), 1);
  EXPECT_EQ(network.GetKshellVertexes(network[14]), 1);

  EXPECT_EQ(network.GetKshellVertexes(network[2]), 2);
  EXPECT_EQ(network.GetKshellVertexes(network[3]), 2);
  EXPECT_EQ(network.GetKshellVertexes(network[12]), 2);
  EXPECT_EQ(network.GetKshellVertexes(network[13]), 2);

  EXPECT_EQ(network.GetKshellVertexes(network[4]), 3);
  EXPECT_EQ(network.GetKshellVertexes(network[6]), 3);
  EXPECT_EQ(network.GetKshellVertexes(network[8]), 3);
  EXPECT_EQ(network.GetKshellVertexes(network[9]), 3);
  EXPECT_EQ(network.GetKshellVertexes(network[5]), 3);
  EXPECT_EQ(network.GetKshellVertexes(network[7]), 3);
  EXPECT_EQ(network.GetKshellVertexes(network[10]), 3);
  EXPECT_EQ(network.GetKshellVertexes(network[11]), 3);
}


TEST(ShortPaths, OnePath){
  class NetTest: public Network{
    public:
    NetTest():Network(8, "test"){
      Network& network(*this);
      CreateEdge(&network[1], &network[2]);  
      CreateEdge(&network[2], &network[3]);  
      CreateEdge(&network[3], &network[4]);  
      CreateEdge(&network[1], &network[5]);  
      CreateEdge(&network[5], &network[4]);  
      CreateEdge(&network[1], &network[6]);  
      CreateEdge(&network[6], &network[7]);  
      CreateEdge(&network[7], &network[4]);  
    };
  } network;

  std::vector<VertexesSet> paths(ShortestPaths(network[1], network[4], 15));
  EXPECT_EQ(&network[1], *paths[0].find(&network[1]));
  EXPECT_EQ(&network[4], *paths[0].find(&network[4]));
  EXPECT_EQ(&network[5], *paths[0].find(&network[5]));

  EXPECT_EQ(ShortestPaths(network[0], network[4], 15).size(), 0);
}

TEST(ShortPaths, TwoPaths){
  class NetTest: public Network{
    public:
    NetTest():Network(8, "test"){
      Network& network(*this);
      CreateEdge(&network[1], &network[0]);  
      CreateEdge(&network[0], &network[4]);  
      CreateEdge(&network[1], &network[2]);  
      CreateEdge(&network[2], &network[3]);  
      CreateEdge(&network[3], &network[4]);  
      CreateEdge(&network[1], &network[5]);  
      CreateEdge(&network[5], &network[4]);  
      CreateEdge(&network[1], &network[6]);  
      CreateEdge(&network[6], &network[7]);  
      CreateEdge(&network[7], &network[4]);  
    };
  } network;
  std::vector<VertexesSet> paths(ShortestPaths(network[1], network[4], 15));

  EXPECT_EQ(&network[1], *paths[0].find(&network[1]));
  EXPECT_EQ(&network[4], *paths[0].find(&network[4]));
  EXPECT_EQ(&network[0], *paths[0].find(&network[0]));

  EXPECT_EQ(&network[1], *paths[1].find(&network[1]));
  EXPECT_EQ(&network[4], *paths[1].find(&network[4]));
  EXPECT_EQ(&network[5], *paths[1].find(&network[5]));
}



TEST(Betweenness, simple){
  class NetTest: public Network{
    public:
    NetTest():Network(8, "test"){
      Network& network(*this);
      CreateEdge(&network[1], &network[2]);  
      CreateEdge(&network[2], &network[3]);  
      CreateEdge(&network[1], &network[3]);  
      CreateEdge(&network[3], &network[4]);  
      CreateEdge(&network[4], &network[6]);  
      CreateEdge(&network[6], &network[5]);  
      CreateEdge(&network[5], &network[7]);  
      CreateEdge(&network[7], &network[6]);  
    };
  } network;

  std::map<unsigned, unsigned> size;
  size[2]=0;
  size[3]=0;
  size[4]=0;

  AllShortestPaths s(network);
  BetweennessCentrality b(network, s);
  EXPECT_NEAR(b.GetBetweenness(&(network[3])), 0.380952, 0.00001);
  EXPECT_NEAR(b.GetBetweenness(&(network[4])), 0.428571, 0.00001);
  EXPECT_NEAR(b.GetBetweenness(&(network[6])), 0.380952, 0.00001);
  EXPECT_NEAR(b.GetBetweenness(&(network[1])), 0.0, 0.00001);
  EXPECT_NEAR(b.GetBetweenness(&(network[2])), 0.0, 0.00001);
  EXPECT_NEAR(b.GetBetweenness(&(network[5])), 0.0, 0.00001);
  EXPECT_NEAR(b.GetBetweenness(&(network[7])), 0.0, 0.00001);
}

TEST(Measures, AllShortPaths){
  class NetTest: public Network{
    public:
    NetTest():Network(8, "test"){
      Network& network(*this);
      CreateEdge(&network[1], &network[2]);  
      CreateEdge(&network[2], &network[3]);  
      CreateEdge(&network[3], &network[4]);  
      CreateEdge(&network[1], &network[5]);  
      CreateEdge(&network[5], &network[4]);  
      CreateEdge(&network[1], &network[6]);  
      CreateEdge(&network[6], &network[7]);  
      CreateEdge(&network[7], &network[4]);  
    };
  } network;

  std::map<unsigned, unsigned> size;
  size[2]=0;
  size[3]=0;
  size[4]=0;

  AllShortestPaths s(network);
  std::cout << std::endl;
  for(size_t m(0); m < 8; ++m)
    for(size_t n(m + 1); n < 8; ++n){
      for(auto i: s.GetPaths(network[m], network[n])){
        ++(size[i.size()]);
      }
    }
  EXPECT_EQ(size[2], 8);
  EXPECT_EQ(size[3], 11);
  EXPECT_EQ(size[4], 4);
}

TEST(Measures, ShortPathsHunger){
  class NetTest: public Network{
    public:
    NetTest():Network(8, "test"){
      Network& network(*this);
      CreateEdge(&network[1], &network[2]);  
      CreateEdge(&network[2], &network[3]);  
      CreateEdge(&network[3], &network[4]);  
      CreateEdge(&network[1], &network[5]);  
      CreateEdge(&network[5], &network[4]);  
      CreateEdge(&network[1], &network[6]);  
      CreateEdge(&network[6], &network[7]);  
      CreateEdge(&network[7], &network[4]);  
    };
  } network;

  std::map<unsigned, unsigned> size;
  size[2]=0;
  size[3]=0;
  size[4]=0;

  std::deque<Path> paths(ShortestPaths_Hunger(network[2]));
  for(auto& i: paths){
      size[i.size()] +=1;
  }
  EXPECT_EQ(size[2], 2);
  EXPECT_EQ(size[3], 3);
  EXPECT_EQ(size[4], 2);

}


