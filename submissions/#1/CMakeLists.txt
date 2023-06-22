FILE(GLOB SRC_FILES [!test|demo]*.cpp)
FILE(GLOB HEADERS *.h)

add_executable(demo_1 demo.cpp ${SRC_FILES} ${HEADERS})
add_executable(test_1 test.cpp ${SRC_FILES} ${HEADERS})
