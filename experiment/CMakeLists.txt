include_directories(${PROJECT_SOURCE_DIR}/experiment/include)
add_library(experiment src/experiment.cpp)
target_link_libraries(experiment edmondsKarp dinic mpm modifiedEdmondsKarp dinicWithDynamicTree)

add_executable(all_experiments run_all_experiments.cpp)
target_link_libraries(all_experiments experiment)
