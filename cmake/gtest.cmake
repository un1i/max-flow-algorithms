include(ExternalProject)
ExternalProject_Add(googletest
        SOURCE_DIR        "${CMAKE_SOURCE_DIR}/3rdparty/googletest"
        PREFIX            "${CMAKE_CURRENT_BINARY_DIR}/googletest"
        BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest/build"
        INSTALL_DIR       "${CMAKE_CURRENT_BINARY_DIR}/googletest/install"
        CONFIGURE_COMMAND "${CMAKE_COMMAND}" -S "${CMAKE_SOURCE_DIR}/3rdparty/googletest/" -B "${CMAKE_CURRENT_BINARY_DIR}/googletest/build/"
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -G${CMAKE_GENERATOR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -Dgtest_force_shared_crt=ON
        BUILD_COMMAND     "${CMAKE_COMMAND}" --build "${CMAKE_CURRENT_BINARY_DIR}/googletest/build" --config ${CMAKE_BUILD_TYPE}
        INSTALL_COMMAND   "${CMAKE_COMMAND}" --install "${CMAKE_CURRENT_BINARY_DIR}/googletest/build" --prefix "${CMAKE_CURRENT_BINARY_DIR}/googletest/install")
