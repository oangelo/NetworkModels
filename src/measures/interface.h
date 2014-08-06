#ifndef INTERFACE_H
#define INTERFACE_H 

#include <unordered_map>

#include "../network.h"


namespace network_models{

  class Measures{
    public:
      Measures();
      virtual ~Measures() = 0;
      double GetMeasure(Vertex* v);
      double operator()(Vertex* v);
      typedef std::unordered_map<Vertex*, double> VertexMeasureMap;
    protected:
      VertexMeasureMap map;
  };

} //namespace

#endif /* INTERFACE_H */
