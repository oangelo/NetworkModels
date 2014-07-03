#ifndef BARABASI_ALBERT_H
#define BARABASI_ALBERT_H

#include <iostream>
#include <vector>
#include <random>

#include "network.h" 

class BarabasiAlbert: public Network{
    public:
        BarabasiAlbert(unsigned size, unsigned connections, unsigned initial_population);
    private:
        std::random_device random_dev;
        std::mt19937 random_generator;
        void PreferentialAttachment(unsigned connections, Vertex& vertex);
};

#endif /* BARABASI_ALBERT_H */
