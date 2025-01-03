#include "edmonds_karp.h"
#include "data_for_tests.h"

#include <gtest/gtest.h>


TEST(edmondsKarp, linearGraph) {
    TestData data = DataForTests::makeLinearGraphData();
    EdmondsKarp edmonds_karp(data.graph);
    edmonds_karp.run();
    EXPECT_EQ(edmonds_karp.getMaxFlow(), data.max_flow);
}

TEST(edmondsKarp, multiplePathsGraph) {
    TestData data = DataForTests::makeMultiplePathsGraphData();
    EdmondsKarp edmonds_karp(data.graph);
    edmonds_karp.run();
    EXPECT_EQ(edmonds_karp.getMaxFlow(), data.max_flow);
}

TEST(edmondsKarp, cycleGraph) {
    TestData data = DataForTests::makeCycleGraphData();
    EdmondsKarp edmonds_karp(data.graph);
    edmonds_karp.run();
    EXPECT_EQ(edmonds_karp.getMaxFlow(), data.max_flow);
}

TEST(edmondsKarp, parallelPathsGraph) {
    TestData data = DataForTests::makeParallelPathsGraphData();
    EdmondsKarp edmonds_karp(data.graph);
    edmonds_karp.run();
    EXPECT_EQ(edmonds_karp.getMaxFlow(), data.max_flow);
}

TEST(edmondsKarp, limitOnSinkGraph) {
    TestData data = DataForTests::makeLimitOnSinkGraphData();
    EdmondsKarp edmonds_karp(data.graph);
    edmonds_karp.run();
    EXPECT_EQ(edmonds_karp.getMaxFlow(), data.max_flow);
}
