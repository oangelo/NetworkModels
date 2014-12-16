#ifndef CLUSTERS_H
#define CLUSTERS_H 

using namespace network_models;

class GenericVertex: public Vertex{
  public:
    int propriety;
    virtual GenericVertex& operator[](size_t index){
      return *dynamic_cast<GenericVertex*>(edges[index].To());
    }
};



bool Compare(Vertex& a, Vertex& b){
  GenericVertex* m(dynamic_cast<GenericVertex*>(&a));
  GenericVertex* n(dynamic_cast<GenericVertex*>(&b));
  if(m->propriety == n->propriety)
    return true;
  else
    return false;
}

TEST(Network, Burn){


  class NetTest: public Network<GenericVertex>{
    public:
      NetTest():Network<GenericVertex>(9, "test"){
        Network<GenericVertex>& network(*this);
        CreateUndirectedEdge(&network[1], &network[2]);  
        CreateUndirectedEdge(&network[1], &network[3]);  
        CreateUndirectedEdge(&network[1], &network[4]);  
        CreateUndirectedEdge(&network[1], &network[5]);  
        CreateUndirectedEdge(&network[5], &network[6]);  
        CreateUndirectedEdge(&network[6], &network[7]);  
        CreateUndirectedEdge(&network[7], &network[8]);  
      };
  } network;
  NetTest net;
  net[1].propriety = 1;
  net[2].propriety = 1;
  net[3].propriety = 1;
  net[4].propriety = 1;
  net[5].propriety = 1;
  net[6].propriety = 0;
  net[7].propriety = 1;
  net[8].propriety = 1;
  EXPECT_EQ(Burn(net[1], Compare).size(), 5);
  EXPECT_EQ(Burn(net[8], Compare).size(), 2);
}

#endif /* CLUSTERS_H */
