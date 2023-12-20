cmake_minimum_required(VERSION 3.5)

project(linked_biguint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(linked_biguint main.cpp
    node.h node.cpp
    biguint.h biguint.cpp)

include(GNUInstallDirs)
install(TARGETS linked_biguint
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
