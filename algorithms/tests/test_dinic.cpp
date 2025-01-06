#include "dinic.h"
#include "data_for_tests.h"

#include <gtest/gtest.h>


TEST(dinic, linearGraph) {
TestData data = DataForTests::makeLinearGraphData();
Dinic dinic(data.graph);
dinic.run();
EXPECT_EQ(dinic.getMaxFlow(), data.max_flow);
}

TEST(dinic, multiplePathsGraph) {
TestData data = DataForTests::makeMultiplePathsGraphData();
Dinic dinic(data.graph);
dinic.run();
EXPECT_EQ(dinic.getMaxFlow(), data.max_flow);
}

TEST(dinic, cycleGraph) {
TestData data = DataForTests::makeCycleGraphData();
Dinic dinic(data.graph);
dinic.run();
EXPECT_EQ(dinic.getMaxFlow(), data.max_flow);
}

TEST(dinic, parallelPathsGraph) {
TestData data = DataForTests::makeParallelPathsGraphData();
Dinic dinic(data.graph);
dinic.run();
EXPECT_EQ(dinic.getMaxFlow(), data.max_flow);
}

TEST(dinic, limitOnSinkGraph) {
TestData data = DataForTests::makeLimitOnSinkGraphData();
Dinic dinic(data.graph);
dinic.run();
EXPECT_EQ(dinic.getMaxFlow(), data.max_flow);
}
