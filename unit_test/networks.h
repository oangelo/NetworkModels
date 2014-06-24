#include "network_models/erdos-renyi.h"
#include "network_models/square.h"
#include "network_models/mean-field.h"

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
