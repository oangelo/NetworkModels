#include "barabasi_albert.h"

BarabasiAlbert::BarabasiAlbert(unsigned size,  unsigned connections, unsigned initial_population)
:Network(2), random_dev(), random_generator(random_dev())
{
    //init the network
    CreateEdge(&operator[](0), &operator[](0));
    for (size_t i = 2; i < initial_population - 2; ++i) {
        NewVertex();
        CreateEdge(&operator[](i), &operator[](i - 1));
    }
}
