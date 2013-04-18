#include "network.h"

Host::Host(): connections(0) {
}

Host& Host::operator++() {
    ++connections;
    return *this;
}

Host::operator unsigned() {
    return connections;
}
