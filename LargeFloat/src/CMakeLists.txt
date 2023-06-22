FILE(GLOB SRC_FILES *.cpp)

add_library(large_float STATIC ${SRC_FILES})
target_link_libraries(large_float large_int)

target_include_directories(large_float PUBLIC "../../LargeInt/src" "${CMAKE_SOURCE_DIR}")

set_target_properties(large_float PROPERTIES LINKER_LANGUAGE CXX)
