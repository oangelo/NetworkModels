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

#endif /* VERTEX_TES_H */
