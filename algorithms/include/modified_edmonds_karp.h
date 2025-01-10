#ifndef MAXFLOW_MODIFIED_EDMONDS_KARP_H
#define MAXFLOW_MODIFIED_EDMONDS_KARP_H

#include "edmonds_karp.h"


class ModifiedEdmondsKarp : public EdmondsKarp {
public:
    explicit ModifiedEdmondsKarp(const Graph& graph);
    void run() override;
};

#endif //MAXFLOW_MODIFIED_EDMONDS_KARP_H
