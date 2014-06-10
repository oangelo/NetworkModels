#include "network_models/erdos-renyi.h"
#include "network_models/square.h"

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
