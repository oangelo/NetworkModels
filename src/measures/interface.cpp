#include "interface.h"

namespace network_models{

  Measures::Measures(): map(){}
  Measures::~Measures(){}

  double Measures::GetMeasure(Vertex* v){
    return map[v];
  }
  double Measures::operator()(Vertex* v){
    return map[v];
  }

}
