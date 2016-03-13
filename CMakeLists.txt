cmake_minimum_required(VERSION 3.3)
project(Regux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Translate.cpp ExprParser.cpp NFA.cpp NFA.h MiniSet.cpp MiniSet.h NFAProxy.cpp NFAProxy.h Regux.cpp Regux.h)
add_executable(Regux ${SOURCE_FILES} NFAProxy.cpp NFAProxy.h Regux.cpp Regux.h)