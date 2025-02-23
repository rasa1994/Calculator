
add_executable(tests Main.cpp)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(tests PRIVATE InputChecker FunctionEvaluator GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

target_sources(tests PRIVATE
${CMAKE_SOURCE_DIR}/${IncludeFolder}/Constants.ixx
)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/${IncludeFolder})
target_link_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/${IncludeFolder})

include(GoogleTest)
gtest_discover_tests(tests)