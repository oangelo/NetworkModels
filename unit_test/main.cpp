#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "gtest/gtest.h"

#include "networks.h"
#include "network_models/vertex.h"
#include "network_models/network.h"
#include "network_models/erdos-renyi.h"
#include "vertex_tes.h"
#include "edge_tes.h"

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

