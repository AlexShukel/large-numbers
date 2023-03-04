FILE(GLOB SRC_FILES *.cpp)

add_library(largeNumbers STATIC ${SRC_FILES})

set_target_properties(largeNumbers PROPERTIES LINKER_LANGUAGE CXX)
