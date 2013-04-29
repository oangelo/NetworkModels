#ifndef VERTEX_TES_H
#define VERTEX_TES_H 


TEST(vertex, add){

    Vertex* from(NULL);
    Vertex* to(NULL);

    Edge ed1(from, to);
    Edge ed2(from, to);
    Vertex vert;
    vert.Add(&ed1);
    vert.Add(&ed2);
    vert.Add(&ed2);

    EXPECT_EQ(vert.size(), 2);
}

TEST(vertex, remove){
    Vertex* from(NULL);
    Vertex* to(NULL);

    Edge ed1(from, to);
    Edge ed2(from, to);

    Vertex vert;
    vert.Add(&ed1);
    vert.Add(&ed2);
    vert.Add(&ed2);
    vert.Remove(&ed2);

    EXPECT_EQ(vert.size(), 1);
}

#endif /* VERTEX_TES_H */
