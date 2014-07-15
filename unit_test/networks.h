#include "network_models/barabasi-albert.h"
#include "network_models/erdos-renyi.h"
#include "network_models/square.h"
#include "network_models/mean-field.h"

using namespace network_models;

class NetworkTest: public Network{
};

TEST(erdos_renyi, construction){
    ErdosRenyi network(2,3);
    EXPECT_EQ(network.size(), 2);
}

TEST(erdos_renyi, edges){
    ErdosRenyi network(100,3);
    unsigned sum(0);
    for (size_t i = 0; i < network.size(); ++i)
    {
        sum += (network[i]).size();
        for (size_t j = 0; j < network[i].size(); ++j){
            EXPECT_EQ(&network[i], network[i](j).From());
        }
    }
    EXPECT_EQ(sum, 6);
}


TEST(erdos_renyi, dot){
    ErdosRenyi network(40,60);
    Graphviz(network, "erdos_renyi.dot");
}

TEST(erdos_renyi, distribution){
    ErdosRenyi network(20,30);
    NodesDistribution(network);
}

TEST(BarabasiAlbert, distribution){
    BarabasiAlbert network(10000, 1, 5);
    auto hist(NodesDistribution(network));
//    for(auto i: hist)
//      std::cout << i.first << " " << i.second << std::endl;
}

TEST(erdos_renyi, MeanConnectivety){
    ErdosRenyi network(40,80);
    EXPECT_NEAR(network.GetMeanConnectivity(), 4, 0.5);
}


TEST(Square, dot){
    Square network(9);
    Graphviz(network, "square.dot");
}

TEST(Square, distribution){
    unsigned nodes = 9;
    Square network(nodes);
    for(auto i: NodesDistribution(network)){
        //No edges with one vertice
        if(i.first == 1)
            EXPECT_EQ(i.second, 0);
        //Only edges on the corners will haeve two vertexes
        if(i.first == 2)
            EXPECT_EQ(i.second, 4);
        //The inside edges will have 4 vertexes
        if(i.first == 4)
            EXPECT_EQ(i.second,nodes -(4*sqrt(nodes)-4));
    }
}

TEST(Square, Burn){
    unsigned nodes = 9;
    Square network(nodes);
    std::set<Vertex*> cluster0(Burn(&network[0]));
    EXPECT_EQ(cluster0.size(), 9);
    network[0].SetMark(1);
    network[0][0].SetMark(1);
    network[0][1].SetMark(1);
    std::set<Vertex*> cluster1(Burn(&network[0]));
    EXPECT_EQ(cluster1.size(), 3);
    network[8].SetMark(2);
    network[8][0].SetMark(2);
    network[8][1].SetMark(2);
    std::set<Vertex*> cluster2(Burn(&network[8]));
    EXPECT_TRUE(cluster2.size() <= 3);
}


TEST(Square, Clusters){
    unsigned nodes = 9;
    Square network(nodes);
    network[0].SetMark(1);
    network[0][0].SetMark(1);
    network[0][1].SetMark(1);
    network[7].SetMark(2);
    network[7][0].SetMark(2);
    network[7][1].SetMark(2);
    std::map<int, std::vector<unsigned>> clusters(Clusters(network));
    EXPECT_EQ(clusters[1][0], 3);
    EXPECT_EQ(clusters[2][0], 3);
}

TEST(MeanField, Nodes){
    unsigned nodes = 9;
    MeanField network(nodes);
    for(size_t i(0); i < network.size(); ++i){
        EXPECT_EQ(network[i].size() + 1, network.size()); 
    }
}

//the k shell of a square network is 2 for all nodes
TEST(kshell, Square){
    unsigned nodes = 100;
    Square network(nodes);
    for(size_t i(0); i < network.size(); ++i){
      unsigned rank(network.GetKshellVertexes(network[i]));
      EXPECT_EQ(rank, 2);
    }
}

TEST(kshell, Barabasi){
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

TEST(kshell, Erdos_Renyi){
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
TEST(kshell, SimpleNet){
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
TEST(kshell, SimpleNet2){
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
