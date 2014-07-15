#ifndef EDGE_TES_H
#define EDGE_TES_H 

using namespace network_models;

TEST(edge, build){
    Vertex from; 
    Vertex to; 
    Edge edge(&from, &to);
    EXPECT_EQ(&from, edge.From());
    EXPECT_EQ(&to, edge.To());
    EXPECT_EQ(false, edge.IsBidirectional());
}

TEST(edge, copy){
    Vertex from; 
    Vertex to; 
    Edge edge_ref(&from, &to);
    Edge edge(edge_ref);
    EXPECT_EQ(&from, edge.From());
    EXPECT_EQ(&to, edge.To());
}

TEST(edge, mark){
    Vertex from; 
    Vertex to; 
    Edge edge(&from, &to);
    EXPECT_EQ(edge.GetMark(), 0);
    edge.SetMark(-4);
    EXPECT_EQ(edge.GetMark(), -4);
}

#endif /* EDGE_TES_H */
