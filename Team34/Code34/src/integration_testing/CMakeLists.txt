file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE data "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.txt")
file(COPY ${data} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/tests")

add_executable(integration_testing ${srcs})
target_link_libraries(integration_testing spa)
add_test(integration_testing integration_testing)
