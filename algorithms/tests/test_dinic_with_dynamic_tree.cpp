#include "dinic_with_dynamic_tree.h"
#include "data_for_tests.h"

#include <gtest/gtest.h>


TEST(dinicWithDynamicTree, linearGraph) {
TestData data = DataForTests::makeLinearGraphData();
DinicWithDynamicTree dinic_with_dynamic_tree(data.graph);
dinic_with_dynamic_tree.run();
EXPECT_EQ(dinic_with_dynamic_tree.getMaxFlow(), data.max_flow);
}

TEST(dinicWithDynamicTree, multiplePathsGraph) {
TestData data = DataForTests::makeMultiplePathsGraphData();
DinicWithDynamicTree dinic_with_dynamic_tree(data.graph);
dinic_with_dynamic_tree.run();
EXPECT_EQ(dinic_with_dynamic_tree.getMaxFlow(), data.max_flow);
}

TEST(dinicWithDynamicTree, cycleGraph) {
TestData data = DataForTests::makeCycleGraphData();
DinicWithDynamicTree dinic_with_dynamic_tree(data.graph);
dinic_with_dynamic_tree.run();
EXPECT_EQ(dinic_with_dynamic_tree.getMaxFlow(), data.max_flow);
}

TEST(dinicWithDynamicTree, parallelPathsGraph) {
TestData data = DataForTests::makeParallelPathsGraphData();
DinicWithDynamicTree dinic_with_dynamic_tree(data.graph);
dinic_with_dynamic_tree.run();
EXPECT_EQ(dinic_with_dynamic_tree.getMaxFlow(), data.max_flow);
}

TEST(dinicWithDynamicTree, limitOnSinkGraph) {
TestData data = DataForTests::makeLimitOnSinkGraphData();
DinicWithDynamicTree dinic_with_dynamic_tree(data.graph);
dinic_with_dynamic_tree.run();
EXPECT_EQ(dinic_with_dynamic_tree.getMaxFlow(), data.max_flow);
}
