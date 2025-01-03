set(edmondsKarp testEdmondsKarp)

add_library(dataForTests data_for_tests.cpp)
target_link_libraries(dataForTests PRIVATE graph)

add_executable(${edmondsKarp} test_edmonds_karp.cpp)
target_include_directories(${edmondsKarp} PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/googletest/googletest/include)
add_dependencies(${edmondsKarp} googletest)
target_link_libraries(${edmondsKarp} PRIVATE edmondsKarp dataForTests gtest gtest_main)
target_link_directories(${edmondsKarp} PUBLIC ${CMAKE_BINARY_DIR}/googletest/install/lib)
add_test(NAME ${edmondsKarp} COMMAND ${edmondsKarp})
