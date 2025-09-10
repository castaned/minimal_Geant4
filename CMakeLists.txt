cmake_minimum_required(VERSION 3.12)
project(linac-minimal)

find_package(Geant4 REQUIRED ui_all vis_all analysis)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/src/*.hh)

add_executable(linac-minimal ${sources} ${headers})
target_link_libraries(linac-minimal ${Geant4_LIBRARIES})
target_compile_features(linac-minimal PRIVATE cxx_std_17)

file(COPY ${PROJECT_SOURCE_DIR}/macros DESTINATION ${PROJECT_BINARY_DIR})
