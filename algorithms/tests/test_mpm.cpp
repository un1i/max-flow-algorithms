#include "mpm.h"
#include "data_for_tests.h"

#include <gtest/gtest.h>


TEST(mpm, linearGraph) {
TestData data = DataForTests::makeLinearGraphData();
MPM mpm(data.graph);
mpm.run();
EXPECT_EQ(mpm.getMaxFlow(), data.max_flow);
}

TEST(mpm, multiplePathsGraph) {
TestData data = DataForTests::makeMultiplePathsGraphData();
MPM mpm(data.graph);
mpm.run();
EXPECT_EQ(mpm.getMaxFlow(), data.max_flow);
}

TEST(mpm, cycleGraph) {
TestData data = DataForTests::makeCycleGraphData();
MPM mpm(data.graph);
mpm.run();
EXPECT_EQ(mpm.getMaxFlow(), data.max_flow);
}

TEST(mpm, parallelPathsGraph) {
TestData data = DataForTests::makeParallelPathsGraphData();
MPM mpm(data.graph);
mpm.run();
EXPECT_EQ(mpm.getMaxFlow(), data.max_flow);
}

TEST(mpm, limitOnSinkGraph) {
TestData data = DataForTests::makeLimitOnSinkGraphData();
MPM mpm(data.graph);
mpm.run();
EXPECT_EQ(mpm.getMaxFlow(), data.max_flow);
}
