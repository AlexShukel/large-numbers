FILE(GLOB SRC_FILES LargeInt/*.cpp LargeDouble/*.cpp *.cpp)

add_library(largeNumbers STATIC ${SRC_FILES})

set_target_properties(largeNumbers PROPERTIES LINKER_LANGUAGE CXX)
