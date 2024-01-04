cmake_minimum_required(VERSION 3.26)
project(Parser)

set(CMAKE_CXX_STANDARD 23)

add_executable(Parser parser.cpp)
add_executable(Regex regex_tokenizer.cpp)
add_executable(Token tokenizer.cpp)
