#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "gtest/gtest.h"

#include "../src/vertex.h"
#include "../src/network.h"
#include "../src/erdos-renyi.h"
#include "../src/measures.h"

#include "vertex_tes.h"
#include "edge_tes.h"
#include "measures_test.h"
#include "networks_test.h"

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

