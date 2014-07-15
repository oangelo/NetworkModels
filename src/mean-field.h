#ifndef MEAN_FIELD_H
#define MEAN_FIELD_H 

#include <random>
#include <iostream>

#include "network.h"


namespace network_models{

  class MeanField: public Network
  {
    public:
      MeanField(unsigned nodes);
    private:
  };

} // namespace end

#endif /* MEAN_FIELD_H */
