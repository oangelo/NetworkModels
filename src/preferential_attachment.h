#ifndef PREFERENTIAL_ATTACHMENT_H
#define PREFERENTIAL_ATTACHMENT_H 

#include <iostream>
#include <vector>
#include <random>

#include "statistics/histogram.h" 


class Host{
    public:
        Host();
        Host& operator++();
        operator unsigned();
    private:
        unsigned connections;
};

std::vector<Host> PreferentialAttachment(unsigned size, unsigned bins, double max);
bool Attachment(Host& host, double probability); 

#endif /* PREFERENTIAL_ATTACHMENT_H */
