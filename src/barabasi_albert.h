#ifndef PREFERENTIAL_ATTACHMENT_H
#define PREFERENTIAL_ATTACHMENT_H 

#include <iostream>
#include <vector>
#include <random>

#include "network.h" 

std::vector<Host> PreferentialAttachment(unsigned size);
bool Attachment(Host& host, double probability); 

#endif /* PREFERENTIAL_ATTACHMENT_H */
