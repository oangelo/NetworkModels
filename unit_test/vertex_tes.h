#ifndef VERTEX_TES_H
#define VERTEX_TES_H 

using namespace network_models;

TEST(vertex, add){

    Vertex to1;
    Vertex to2;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);
    Edge ed3(&to1, &to2);

    vert.Add(ed1);
    EXPECT_EQ(vert.size(), 1);
    vert.Add(ed2);
    EXPECT_EQ(vert.size(), 2);
    EXPECT_THROW(vert.Add(ed2), std::invalid_argument);
    EXPECT_THROW(vert.Add(ed3), std::invalid_argument);
}

TEST(vertex, iterator){
    Vertex to1;
    Vertex to2;
    Vertex to3;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);
    Edge ed3(&vert, &to3);

    vert.Add(ed1);
    vert.Add(ed2);
    vert.Add(ed3);
    EXPECT_EQ(*vert.begin(), ed1);
    EXPECT_EQ(*(vert.begin()+1), ed2);
    EXPECT_EQ(*(vert.end()-1), ed3);
}

TEST(vertex, remove){
    Vertex to1;
    Vertex to2;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);
    Edge ed3(&to1, &to2);

    vert.Add(ed1);
    vert.Add(ed2);
    EXPECT_EQ(vert.size(), 2);
    vert.Remove(ed2);
    EXPECT_EQ(vert.size(), 1);
    vert.Remove(ed1);
    EXPECT_EQ(vert.size(), 0);
    EXPECT_THROW(vert.Remove(ed3), std::invalid_argument);
}

TEST(vertex, RemoveVertex){
    Vertex to1;
    Vertex to2;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);
    Edge ed3(&to1, &to2);

    vert.Add(ed1);
    vert.Add(ed2);
    EXPECT_EQ(vert.size(), 2);
    vert.Remove(to1);
    EXPECT_EQ(vert.size(), 1);
    vert.Remove(to2);
    EXPECT_EQ(vert.size(), 0);
}

TEST(vertex, _operator){
    Vertex to1;
    Vertex to2;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);

    vert.Add(ed1);
    vert.Add(ed2);

    EXPECT_EQ(vert(0).From(), &vert);
    EXPECT_EQ(vert(1).From(), &vert);

    EXPECT_EQ(vert(0).To(), &to1);
    EXPECT_EQ(vert(1).To(), &to2);
}

TEST(vertex, copy){
    Vertex to1;
    Vertex to2;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);

    vert.Add(ed1);
    vert.Add(ed2);

    Vertex copy(vert);
    EXPECT_EQ(copy(0).To(), &to1);
    EXPECT_EQ(copy(1).To(), &to2);
}


TEST(vertex, comparison){
    Vertex v1;
    Vertex v2;

    EXPECT_TRUE(v1 == v1);
    EXPECT_FALSE(v1 == v2);
}

TEST(vertex, repeated_edge){
    Vertex to1;
    Vertex to2;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);

    vert.Add(ed1);
    EXPECT_THROW(vert.Add(ed1), std::invalid_argument);
    vert.Add(ed2);
}

#endif /* VERTEX_TES_H */
