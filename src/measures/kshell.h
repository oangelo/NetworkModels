#ifndef KSHELL_H
#define KSHELL_H 

#include "interface.h"

namespace network_models {
  //k-shell algorithm (ref arXiv:cs/0310049v1)
  class Kshell: public Measures{
    public:
      Kshell(Network& network);
    private:
      void BuildKshell(Network& network);
  };

}

#endif /* KSHELL_H */
