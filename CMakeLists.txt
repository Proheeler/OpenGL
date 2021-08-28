project(c20)
set (CMAKE_CXX_STANDARD 20)
find_package(Threads)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pthread OpenGL::OpenGL ${GLUT_LIBRARY})
add_dependencies(${PROJECT_NAME} OpenGL::OpenGL)