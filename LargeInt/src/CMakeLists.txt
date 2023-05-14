FILE(GLOB SRC_FILES *.cpp)

add_library(large_int STATIC ${SRC_FILES})

set_target_properties(large_int PROPERTIES LINKER_LANGUAGE CXX)
