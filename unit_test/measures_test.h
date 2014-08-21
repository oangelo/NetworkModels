#include "../src/square.h"
#include "../src/barabasi-albert.h"
#include "../src/mean-field.h"
#include "../src/measures.h"

using namespace network_models;

//the k shell of a square network is 2 for all nodes
TEST(measures, kshellSquare){
    unsigned nodes = 100;
    Square<Vertex> network(nodes);
    Kshell kshell(network);
    for(size_t i(0); i < network.size(); ++i){
      unsigned rank(kshell(&network[i]));
      EXPECT_EQ(rank, 2);
    }
}

TEST(measures, kshellBarabasi){
    unsigned nodes(25);
    unsigned m(8);
    BarabasiAlbert<Vertex> network(nodes, m, 10);
//    Graphviz(network, "kshell_BA.dot");
    std::vector<unsigned> aux;
    Kshell kshell(network);
    for(size_t i(0); i < network.size(); ++i){
      unsigned rank(kshell(&network[i]));
      aux.push_back(rank);
    }
    EXPECT_TRUE(*std::max_element(aux.begin(), aux.end()) <= m);
}

TEST(measures, kshellErdos_Renyi){
    unsigned nodes(1125);
    unsigned m(8);
    ErdosRenyi<Vertex> network(nodes, m*nodes);
//    Graphviz(network, "kshell_ER.dot");
    std::vector<unsigned> aux;
    Kshell kshell(network);
    for(Network<Vertex>::iterator it(network.begin()); it < network.end(); ++it){
      unsigned rank(kshell(&(*it)));
      aux.push_back(rank);
    }
    EXPECT_TRUE(*std::max_element(aux.begin(), aux.end()) <= 2*m);
}

//partial example(right) of reference arXiv:cs/0310049v1
TEST(measures, kshellSimpleNet){
  class NetTest: public Network<Vertex>{
    public:
    NetTest():Network<Vertex>(6, "test"){
      Network<Vertex>& network(*this);
      CreateUndirectedEdge(&network[1], &network[2]);  
      CreateUndirectedEdge(&network[2], &network[4]);  
      CreateUndirectedEdge(&network[3], &network[4]);  
      CreateUndirectedEdge(&network[3], &network[1]);  
      CreateUndirectedEdge(&network[0], &network[1]);  
    };
  } network;
    
  Kshell kshell(network);
  EXPECT_EQ(kshell(&network[0]), 1);
  EXPECT_EQ(kshell(&network[1]), 2);
  EXPECT_EQ(kshell(&network[2]), 2);
  EXPECT_EQ(kshell(&network[3]), 2);
  EXPECT_EQ(kshell(&network[4]), 2);
  EXPECT_EQ(kshell(&network[5]), 0);
}

//partial example(left) of reference arXiv:cs/0310049v1
TEST(measures, kshellSimpleNet2){
  class NetTest: public Network<Vertex>{
    public:
    NetTest():Network<Vertex>(15, "test"){
      Network<Vertex>& network(*this);
      CreateUndirectedEdge(&network[0], &network[2]);  
      CreateUndirectedEdge(&network[1], &network[2]);  
      CreateUndirectedEdge(&network[2], &network[3]);  
      CreateUndirectedEdge(&network[2], &network[5]);  
      CreateUndirectedEdge(&network[3], &network[4]);  
      CreateUndirectedEdge(&network[3], &network[5]);  
      CreateUndirectedEdge(&network[4], &network[8]);  
      CreateUndirectedEdge(&network[4], &network[9]);  
      CreateUndirectedEdge(&network[4], &network[6]);  
      CreateUndirectedEdge(&network[6], &network[8]);  
      CreateUndirectedEdge(&network[6], &network[9]);  
      CreateUndirectedEdge(&network[8], &network[9]);  
      CreateUndirectedEdge(&network[5], &network[7]);  
      CreateUndirectedEdge(&network[5], &network[10]);  
      CreateUndirectedEdge(&network[5], &network[11]);  
      CreateUndirectedEdge(&network[7], &network[10]);  
      CreateUndirectedEdge(&network[7], &network[11]);  
      CreateUndirectedEdge(&network[10], &network[11]);  
      CreateUndirectedEdge(&network[9], &network[10]);  
      CreateUndirectedEdge(&network[9], &network[12]);  
      CreateUndirectedEdge(&network[10], &network[12]);  
      CreateUndirectedEdge(&network[10], &network[13]);  
      CreateUndirectedEdge(&network[12], &network[13]);  
      CreateUndirectedEdge(&network[12], &network[14]);  
    };
  } network;
  Kshell kshell(network);
  //Graphviz(network, "kshell_test2.dot");
  EXPECT_EQ(kshell(&network[0]), 1);
  EXPECT_EQ(kshell(&network[1]), 1);
  EXPECT_EQ(kshell(&network[14]), 1);

  EXPECT_EQ(kshell(&network[2]), 2);
  EXPECT_EQ(kshell(&network[3]), 2);
  EXPECT_EQ(kshell(&network[12]), 2);
  EXPECT_EQ(kshell(&network[13]), 2);

  EXPECT_EQ(kshell(&network[4]), 3);
  EXPECT_EQ(kshell(&network[6]), 3);
  EXPECT_EQ(kshell(&network[8]), 3);
  EXPECT_EQ(kshell(&network[9]), 3);
  EXPECT_EQ(kshell(&network[5]), 3);
  EXPECT_EQ(kshell(&network[7]), 3);
  EXPECT_EQ(kshell(&network[10]), 3);
  EXPECT_EQ(kshell(&network[11]), 3);
}


TEST(ShortPaths, OnePath){
  class NetTest: public Network<Vertex>{
    public:
    NetTest():Network<Vertex>(8, "test"){
      Network<Vertex>& network(*this);
      CreateUndirectedEdge(&network[1], &network[2]);  
      CreateUndirectedEdge(&network[2], &network[3]);  
      CreateUndirectedEdge(&network[3], &network[4]);  
      CreateUndirectedEdge(&network[1], &network[5]);  
      CreateUndirectedEdge(&network[5], &network[4]);  
      CreateUndirectedEdge(&network[1], &network[6]);  
      CreateUndirectedEdge(&network[6], &network[7]);  
      CreateUndirectedEdge(&network[7], &network[4]);  
    };
  } network;

  std::vector<VertexesSet> paths(ShortestPaths(network[1], network[4], 15));
  EXPECT_EQ(&network[1], *paths[0].find(&network[1]));
  EXPECT_EQ(&network[4], *paths[0].find(&network[4]));
  EXPECT_EQ(&network[5], *paths[0].find(&network[5]));

  EXPECT_EQ(ShortestPaths(network[0], network[4], 15).size(), 0);
}

TEST(ShortPaths, TwoPaths){
  class NetTest: public Network<Vertex>{
    public:
    NetTest():Network<Vertex>(8, "test"){
      Network<Vertex>& network(*this);
      CreateUndirectedEdge(&network[1], &network[0]);  
      CreateUndirectedEdge(&network[0], &network[4]);  
      CreateUndirectedEdge(&network[1], &network[2]);  
      CreateUndirectedEdge(&network[2], &network[3]);  
      CreateUndirectedEdge(&network[3], &network[4]);  
      CreateUndirectedEdge(&network[1], &network[5]);  
      CreateUndirectedEdge(&network[5], &network[4]);  
      CreateUndirectedEdge(&network[1], &network[6]);  
      CreateUndirectedEdge(&network[6], &network[7]);  
      CreateUndirectedEdge(&network[7], &network[4]);  
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
  class NetTest: public Network<Vertex>{
    public:
    NetTest():Network<Vertex>(8, "test"){
      Network<Vertex>& network(*this);
      CreateUndirectedEdge(&network[1], &network[2]);  
      CreateUndirectedEdge(&network[2], &network[3]);  
      CreateUndirectedEdge(&network[1], &network[3]);  
      CreateUndirectedEdge(&network[3], &network[4]);  
      CreateUndirectedEdge(&network[4], &network[6]);  
      CreateUndirectedEdge(&network[6], &network[5]);  
      CreateUndirectedEdge(&network[5], &network[7]);  
      CreateUndirectedEdge(&network[7], &network[6]);  
    };
  } network;

  std::map<unsigned, unsigned> size;
  size[2]=0;
  size[3]=0;
  size[4]=0;

  BetweennessCentrality b(network);
  EXPECT_NEAR(b(&(network[3])), 0.380952, 0.00001);
  EXPECT_NEAR(b(&(network[4])), 0.428571, 0.00001);
  EXPECT_NEAR(b(&(network[6])), 0.380952, 0.00001);
  EXPECT_NEAR(b(&(network[1])), 0.0, 0.00001);
  EXPECT_NEAR(b(&(network[2])), 0.0, 0.00001);
  EXPECT_NEAR(b(&(network[5])), 0.0, 0.00001);
  EXPECT_NEAR(b(&(network[7])), 0.0, 0.00001);
}


TEST(Measures, ShortPathsHunger){
  class NetTest: public Network<Vertex>{
    public:
    NetTest():Network<Vertex>(8, "test"){
      Network<Vertex>& network(*this);
      CreateUndirectedEdge(&network[1], &network[2]);  
      CreateUndirectedEdge(&network[2], &network[3]);  
      CreateUndirectedEdge(&network[3], &network[4]);  
      CreateUndirectedEdge(&network[1], &network[5]);  
      CreateUndirectedEdge(&network[5], &network[4]);  
      CreateUndirectedEdge(&network[1], &network[6]);  
      CreateUndirectedEdge(&network[6], &network[7]);  
      CreateUndirectedEdge(&network[7], &network[4]);  
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

//TEST(measures, BetweennessTime){
//  ErdosRenyi network(2000, 4000);
//  BetweennessCentrality b(network);
//}

//TEST(measures, BetweennessDist){
//  BarabasiAlbert network(2000, 3, 5);
//  BetweennessCentrality b(network);
//  std::ofstream file;
//  file.open("betweenness_barabasi.csv");
//  for(auto& i: network)
//    file << b.GetBetweenness(&i) << std::endl;
//}

TEST(Measures, EigenVectorCentrality){
  class NetTest: public Network<Vertex>{
    public:
    NetTest():Network<Vertex>(15, "test"){
      Network<Vertex>& network(*this);
      CreateUndirectedEdge(&network[0], &network[1]);  
      CreateUndirectedEdge(&network[1], &network[2]);  
      CreateUndirectedEdge(&network[1], &network[3]);  
      CreateUndirectedEdge(&network[1], &network[4]);  
      CreateUndirectedEdge(&network[1], &network[6]);  
      CreateUndirectedEdge(&network[4], &network[5]);  

      CreateUndirectedEdge(&network[0], &network[7]);  
      CreateUndirectedEdge(&network[0], &network[8]);  
      CreateUndirectedEdge(&network[0], &network[9]);  
      CreateUndirectedEdge(&network[0], &network[10]);  
      CreateUndirectedEdge(&network[0], &network[11]);  
      CreateUndirectedEdge(&network[0], &network[12]);  
      CreateUndirectedEdge(&network[0], &network[14]);  
      CreateUndirectedEdge(&network[12], &network[13]);  
    };
  } network;
  EigenVectorCentrality evc(network);
  EXPECT_TRUE(evc(&network[0]) > evc(&network[1]));
  for(size_t i(2); i < network.size(); ++i){
    EXPECT_TRUE(evc(&network[1]) > evc(&network[i]));
  }
}

