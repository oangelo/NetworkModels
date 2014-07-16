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
    vert.Add(ed2);
    EXPECT_EQ(vert.size(), 2);
    EXPECT_FALSE(vert.Add(ed3));
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

    vert.Add(ed1);
    vert.Add(ed2);
    EXPECT_EQ(vert.size(), 2);
    vert.Remove(ed2);
    EXPECT_EQ(vert.size(), 1);
    vert.Remove(ed1);
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

TEST(vertex, find){
    Vertex to1;
    Vertex to2;
    Vertex to3;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);
    Edge ed3(&vert, &to3);

    vert.Add(ed1);
    vert.Add(ed2);

    EXPECT_EQ(to1.FindIncoming(&vert), &(vert(0)));
    EXPECT_EQ(to2.FindIncoming(&vert), &(vert(1)));
    Edge* e(NULL);
    EXPECT_EQ(to3.FindIncoming(&vert), e);
    EXPECT_EQ(vert.FindIncoming(&to3), e);
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

    EXPECT_TRUE(vert.Add(ed1));
    EXPECT_FALSE(vert.Add(ed1));
    EXPECT_TRUE(vert.Add(ed2));
}

TEST(vertex, mark){
    Vertex v1;

    EXPECT_EQ(v1.GetMark(), 0);
    v1.SetMark(-2);
    EXPECT_EQ(v1.GetMark(), -2);
}
#endif /* VERTEX_TES_H */
