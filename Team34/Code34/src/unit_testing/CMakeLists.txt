enable_testing()
file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE data "${CMAKE_CURRENT_SOURCE_DIR}/src/*.txt")
file(COPY ${data} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/tests")

add_executable(unit_testing ${srcs})
target_link_libraries(unit_testing spa)
add_test(unit_testing unit_testing)
