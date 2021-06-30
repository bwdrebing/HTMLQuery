cmake_minimum_required(VERSION 3.19)

add_executable(HTMLQuery_test 
  run_all_tests.cpp
  tUtils.cpp
  tCountingVisitor.cpp
  tHtmlQueryEngine.cpp
  assets/ManyUrls.txt
  assets/EmptyFile.txt
  assets/DuplicateUrls.txt
)

target_link_libraries(HTMLQuery_test PUBLIC
  HTMLQuery_lib
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(HTMLQuery_test PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

add_test(
  NAME HTMLQuery_test
  COMMAND HTMLQuery_test
)

add_custom_command(
     TARGET HTMLQuery_test
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND HTMLQuery_test
     WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test"

)

