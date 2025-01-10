#include "modified_edmonds_karp.h"
#include "data_for_tests.h"

#include <gtest/gtest.h>


TEST(modifiedEdmondsKarp, linearGraph) {
TestData data = DataForTests::makeLinearGraphData();
ModifiedEdmondsKarp modified_edmonds_karp(data.graph);
modified_edmonds_karp.run();
EXPECT_EQ(modified_edmonds_karp.getMaxFlow(), data.max_flow);
}

TEST(modifiedEdmondsKarp, multiplePathsGraph) {
TestData data = DataForTests::makeMultiplePathsGraphData();
ModifiedEdmondsKarp modified_edmonds_karp(data.graph);
modified_edmonds_karp.run();
EXPECT_EQ(modified_edmonds_karp.getMaxFlow(), data.max_flow);
}

TEST(modifiedEdmondsKarp, cycleGraph) {
TestData data = DataForTests::makeCycleGraphData();
ModifiedEdmondsKarp modified_edmonds_karp(data.graph);
modified_edmonds_karp.run();
EXPECT_EQ(modified_edmonds_karp.getMaxFlow(), data.max_flow);
}

TEST(modifiedEdmondsKarp, parallelPathsGraph) {
TestData data = DataForTests::makeParallelPathsGraphData();
ModifiedEdmondsKarp modified_edmonds_karp(data.graph);
modified_edmonds_karp.run();
EXPECT_EQ(modified_edmonds_karp.getMaxFlow(), data.max_flow);
}

TEST(modifiedEdmondsKarp, limitOnSinkGraph) {
TestData data = DataForTests::makeLimitOnSinkGraphData();
ModifiedEdmondsKarp modified_edmonds_karp(data.graph);
modified_edmonds_karp.run();
EXPECT_EQ(modified_edmonds_karp.getMaxFlow(), data.max_flow);
}
