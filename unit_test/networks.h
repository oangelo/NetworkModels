#include "../src/erdos-renyi.h"

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
            EXPECT_EQ(&network[i], network[i][j].From());
        }
    }
    EXPECT_EQ(sum, 6);
}


TEST(erdos_renyi, dot){
    ErdosRenyi network(20,30);
    Graphviz(network, "test.dot");
}

TEST(erdos_renyi, distribution){
    ErdosRenyi network(20,30);
    NodesDistribution(network);
}
