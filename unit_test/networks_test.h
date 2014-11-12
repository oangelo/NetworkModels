#include "../src/barabasi-albert.h"
#include "../src/barabasi-albert-extended.h"
#include "../src/erdos-renyi.h"
#include "../src/square.h"
#include "../src/mean-field.h"
#include "../src/real-network.h"
#include "../src/utilities.h"
#include "../src/models/configurational.h"
#include <fstream>

using namespace network_models;

TEST(Network, Generic){
  class GenericVertex: public Vertex{
    public:
      int propriety;
      virtual GenericVertex& operator[](size_t index){
        return *dynamic_cast<GenericVertex*>(edges[index].To());
      }
  };

  class NetTest: public Network<GenericVertex>{
    public:
      NetTest():Network<GenericVertex>(2, "test"){
        Network<GenericVertex>& network(*this);
        CreateUndirectedEdge(&network[0], &network[1]);  
      };
  } network;

  network[0].propriety = 1;
  network[1].propriety = 2;

  EXPECT_EQ(network.size(), 2);
  EXPECT_EQ(network[0].propriety, 1);
  EXPECT_EQ(network[1].propriety, 2);
  EXPECT_EQ(network[0][0].propriety, 2);
  EXPECT_EQ(network[1][0].propriety, 1);
}

TEST(Network, RemoveUndirected){
  class GenericVertex: public Vertex{
    public:
      int propriety;
      virtual GenericVertex& operator[](size_t index){
        return *dynamic_cast<GenericVertex*>(edges[index].To());
      }
  };

  class NetTest: public Network<GenericVertex>{
    public:
      NetTest():Network<GenericVertex>(3, "test"){
        Network<GenericVertex>& network(*this);
        CreateUndirectedEdge(&network[0], &network[1]);  
        CreateUndirectedEdge(&network[0], &network[2]);  
        RemoveUndirectedEdge(&network[0], &network[1]);  
        EXPECT_THROW(RemoveUndirectedEdge(&network[0], &network[1]), std::invalid_argument);  
      };
  } network;

  EXPECT_EQ(network[1].size(), 0);
  EXPECT_EQ(network[0].size(), 1);
  EXPECT_EQ(network[2].size(), 1);
}

TEST(Network, ErdosRenyiConstruction){
  ErdosRenyi<Vertex> network(12,3);
  EXPECT_EQ(network.size(), 12);
  EXPECT_THROW(ErdosRenyi<Vertex>(10, 100), std::range_error);
}

TEST(Nerwork, ErdosRenyiEdges){
  unsigned edges(200);
  ErdosRenyi<Vertex> network(100, edges);
  unsigned sum(0);
  for (size_t i = 0; i < network.size(); ++i)
  {
    sum += (network[i]).size();
    for (size_t j = 0; j < network[i].size(); ++j){
      EXPECT_EQ(&network[i], network[i](j).From());
    }
  }
  EXPECT_EQ(sum, 2 * edges);
}


TEST(Network, ErdosRenyiDot){
  ErdosRenyi<Vertex> network(40,40);
  Graphviz(network, "erdos_renyi.dot");
}

TEST(Network, ErdosRenyiDist){
  ErdosRenyi<Vertex> network(100000,1000000);
  std::vector<unsigned> degrees;
  for(Network<Vertex>::iterator it(network.begin());
      it != network.end(); ++it){
    degrees.push_back(it->size());
  }
  std::sort(degrees.begin(), degrees.end(), [] (unsigned a, unsigned b){return a > b;});
  std::ofstream myfile;
  myfile.open ("erdos_dist.txt");
  for(auto i: degrees)
    myfile << i << std::endl;

}

TEST(BarabasiAlbert, distribution){
  BarabasiAlbert<Vertex> network(10000, 5, 5);
  std::vector<unsigned> degrees;
  for(Network<Vertex>::iterator it(network.begin());
      it != network.end(); ++it){
    degrees.push_back(it->size());
  }
  std::sort(degrees.begin(), degrees.end(), [] (unsigned a, unsigned b){return a > b;});
  std::ofstream myfile;
  myfile.open ("barabasi_dist.txt");
  for(auto i: degrees)
    myfile << i << std::endl;
}

TEST(erdos_renyi, MeanConnectivety){
  ErdosRenyi<Vertex> network(1000,100);
  EXPECT_NEAR(network.GetMeanConnectivity(), 200.0 / 1000.0, 0.01);
}

TEST(Square, dot){
  Square<Vertex> network(9);
  Graphviz(network, "square.dot");
}

TEST(Square, distribution){
  unsigned nodes = 9;
  Square<Vertex> network(nodes);
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

//TEST(Square, Burn){
//    unsigned nodes = 9;
//    Square<Vertex> network(nodes);
//    std::set<Vertex*> cluster0(Burn(&network[0]));
//    EXPECT_EQ(cluster0.size(), 9);
//    network[0].SetMark(1);
//    network[0][0].SetMark(1);
//    network[0][1].SetMark(1);
//    std::set<Vertex*> cluster1(Burn(&network[0]));
//    EXPECT_EQ(cluster1.size(), 3);
//    network[8].SetMark(2);
//    network[8][0].SetMark(2);
//    network[8][1].SetMark(2);
//    std::set<Vertex*> cluster2(Burn(&network[8]));
//    EXPECT_TRUE(cluster2.size() <= 3);
//}


//TEST(Square, Clusters){
//    unsigned nodes = 9;
//    Square<Vertex> network(nodes);
//    network[0].SetMark(1);
//    network[0][0].SetMark(1);
//    network[0][1].SetMark(1);
//    network[7].SetMark(2);
//    network[7][0].SetMark(2);
//    network[7][1].SetMark(2);
//    std::map<int, std::vector<unsigned>> clusters(Clusters(network));
//    EXPECT_EQ(clusters[1][0], 3);
//    EXPECT_EQ(clusters[2][0], 3);
//}

TEST(MeanField, Nodes){
  unsigned nodes = 9;
  MeanField<Vertex> network(nodes);
  for(size_t i(0); i < network.size(); ++i){
    EXPECT_EQ(network[i].size() + 1, network.size()); 
  }
}

TEST(Network, RealNetworks){
  //write a square network to a file
  unsigned nodes = 9;
  Square<Vertex> network(nodes);
  std::unordered_map<Vertex*, unsigned> map;
  for(Network<Vertex>::iterator i(network.begin()); i != network.end(); ++i)
    map[&(*i)] = std::distance(network.begin(), i);
  std::ofstream myfile;
  myfile.open ("square.txt");
  for(Network<Vertex>::iterator i(network.begin()); i != network.end(); ++i)
    for(auto& v: *i)
      myfile << map[v.From()] << "\t" << map[v.To()] << std::endl;
  //Read Square network from a file and test it
  RealDirectedNetwork<Vertex> real("square.txt");
  for(auto i: NodesDistribution(real)){
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

TEST(Network, isUndirected){
  unsigned nodes = 9;
  Square<Vertex> network(nodes);
  class NetworkTest: public Network<Vertex>{
    public:
      NetworkTest():Network<Vertex>(4, "teste"){
        Network<Vertex>& network(*this);
        network[0].Add(Edge(&network[0],&network[2]));
      }
  } teste;
  EXPECT_TRUE(IsUndirected(network.begin(), network.end()));
  EXPECT_FALSE(IsUndirected(teste.begin(), teste.end()));
}

TEST(Network, BarabasiExtended){
  BarabasiAlbertExtended<Vertex> network(100, 100, 50, 0.1, 0.1);
  std::ofstream myfile;
  myfile.open ("barabasi_extended.txt");
  for(auto i: network)
    myfile << i.size() << std::endl;
}

TEST(Network, BarabasiAlbertConstruction){
  EXPECT_THROW(BarabasiAlbert<Vertex>(10, 100, 5), std::range_error);
}

TEST(Network, Configurational){
  unsigned samples(100000);
  Configurational<Vertex> network(PowerLaw(-1.5, samples, 5, 0.01*samples));
  std::ofstream myfile;
  myfile.open ("configurational.txt");
  for(auto i: network)
    myfile << i.size() << std::endl;
}
