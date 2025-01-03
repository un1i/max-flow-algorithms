#ifndef MAXFLOW_EDGE_ADJ_H
#define MAXFLOW_EDGE_ADJ_H

struct EdgeAdj {
    int end;
    int capacity;
    EdgeAdj(int end, int capacity) : end{end}, capacity{capacity} {};
};

#endif //MAXFLOW_EDGE_ADJ_H
