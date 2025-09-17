cmake_minimum_required(VERSION 3.12)
project(minimal_linac)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})


include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(minimal_linac main.cc ${sources} ${headers})
target_link_libraries(minimal_linac ${Geant4_LIBRARIES})

# Para tener macros en el build
# set(CMAKE_INSTALL_PREFIX init.mac)
file(COPY ${PROJECT_SOURCE_DIR}/macros DESTINATION ${PROJECT_BINARY_DIR})
