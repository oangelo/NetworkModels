#ifndef UTILITIES_H
#define UTILITIES_H 

#include "network.h"


namespace network_models{

  template<typename iterator>
  bool IsBidirectional(iterator begin, iterator end){
    for(iterator i(begin); i < end; ++i){
      for(auto& j: *i){
        Vertex& to(*(j.To()));
        auto it(std::find_if(to.begin(), to.end(), [&i] (Edge& a){
          return a.To() == &(*i);
        }));
        if(it == to.end())
          return false;
      }
    }
    return true;
  }

} //namespace

#endif /* UTILITIES_H */
