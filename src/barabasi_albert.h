#ifndef PREFERENTIAL_ATTACHMENT_H
#define PREFERENTIAL_ATTACHMENT_H 

#include <iostream>
#include <vector>
#include <random>

#include "network.h" 

class BarabasiAlbert: public Network{
    public:
        BarabasiAlbert(unsigned size, unsigned connections, unsigned initial_population);
        Vertex* PreferentialAttachment(); 
    private:
        std::random_device random_dev;
        std::mt19937 random_generator;
};


#endif /* PREFERENTIAL_ATTACHMENT_H */
