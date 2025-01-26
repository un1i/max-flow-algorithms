add_library(node node.cpp)

add_library(splayTree splay_tree.cpp)
target_link_libraries(splayTree node)

add_library(linkCutTree link_cut_tree.cpp)
target_link_libraries(linkCutTree splayTree)
