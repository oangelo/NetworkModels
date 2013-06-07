#ifndef VERTEX_TES_H
#define VERTEX_TES_H 


TEST(vertex, add){

    Vertex to1;
    Vertex to2;

    Vertex vert;
    Edge ed1(&vert, &to1);
    Edge ed2(&vert, &to2);

    vert.Add(ed1);
    EXPECT_EQ(vert.size(), 1);
    vert.Add(ed2);
    EXPECT_EQ(vert.size(), 2);
    vert.Add(ed2);
    EXPECT_EQ(vert.size(), 2);
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
#endif /* VERTEX_TES_H */
