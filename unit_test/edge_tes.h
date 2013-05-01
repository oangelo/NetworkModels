#ifndef EDGE_TES_H
#define EDGE_TES_H 

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

#endif /* EDGE_TES_H */
