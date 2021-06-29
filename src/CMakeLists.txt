cmake_minimum_required(VERSION 3.19)


add_library(HTMLQuery_lib
  utils.cpp
  utils.h
  HtmlQueryEngine.cpp  HtmlQueryEngine.h 
  NodePredicates.cpp  NodePredicates.h
   visitors/IGumboNodeVisitor.h visitors/IGumboNodeVisitor.cpp
  visitors/CountingVisitor.cpp  visitors/CountingVisitor.h 
)

find_package(CURL CONFIG REQUIRED)
find_package(gumbo)
target_link_libraries(HTMLQuery_lib PRIVATE CURL::libcurl PUBLIC gumbo::gumbo)

#This project should compile main.cpp into an executable named CMake_Example.exe
add_executable(HTMLQuery
  main.cpp
)

target_link_libraries(HTMLQuery PRIVATE HTMLQuery_lib)