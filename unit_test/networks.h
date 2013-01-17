#include "../src/preferential_attachment.h"

TEST(Network, constructor){
    Host host;
    unsigned connections = host;
    EXPECT_EQ(connections, 0);
}

TEST(Network, copy){
    Host host1;
    ++host1;
    Host host2 = host1;
    unsigned connections = host2;
    EXPECT_EQ(connections, 1);
}

TEST(Network, increment){
    Host host;
    ++host;
    unsigned connections = host;
    EXPECT_EQ(connections, 1);
}

TEST(Network, attachment){
    Host host;
    Attachment(host, 1);
    unsigned connections = host;
    EXPECT_EQ(connections, 1);
    Attachment(host, 0);
    connections = host;
    EXPECT_EQ(connections, 1);
}
TEST(Network, preferential_attachment){
    PreferentialAttachment(100000000);
}
