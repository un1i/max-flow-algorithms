add_library(algorithm algorithm.cpp)

add_library(edmondsKarp edmonds_karp.cpp)
target_link_libraries(edmondsKarp graph algorithm)

add_library(dinic dinic.cpp)
target_link_libraries(dinic graph algorithm)
