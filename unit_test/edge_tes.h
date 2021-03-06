#ifndef EDGE_TES_H
#define EDGE_TES_H 

using namespace network_models;

TEST(edge, build){
    Vertex from; 
    Vertex to; 
    Edge edge(&from, &to);
    EXPECT_EQ(&from, edge.From());
    EXPECT_EQ(&to, edge.To());
}

TEST(edge, copy){
    Vertex from; 
    Vertex to; 
    Edge edge_ref(&from, &to);
    Edge edge(edge_ref);
    EXPECT_EQ(&from, edge.From());
    EXPECT_EQ(&to, edge.To());
}

#endif /* EDGE_TES_H */
