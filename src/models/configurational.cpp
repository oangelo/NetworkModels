#include "configurational.h"

namespace network_models{
  std::vector<unsigned> PowerLaw(double exponent, unsigned samples, unsigned min, unsigned max){

    std::vector<double> values;
    std::vector<unsigned> distribution;
    std::random_device rd;
    std::mt19937 gen(rd());
    double min_val(100000000);

    for(size_t i(0); i < 10 * samples; ++i){
      double rv(pow(gen(),  1.0 /(1 + exponent)));
        values.push_back(rv);
      if(rv < min_val)
        min_val = rv;
    }

    for(auto& i: values){
      unsigned aux(static_cast<int>(i / min_val));
      if(aux > min and aux < max)
        distribution.push_back(aux);
    }

    return distribution;
  }
}
