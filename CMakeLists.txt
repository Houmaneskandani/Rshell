CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
     src/command.cpp
     src/and.cpp
     src/or.cpp
     src/main.cpp
     src/semicolon.cpp 
     src/parse.cpp
     src/pipe.cpp
     src/input_redirect.cpp
     src/output_redirect_append.cpp 
     src/output_redirect.cpp    
    src/testcommand.cpp
)


ADD_EXECUTABLE(test
     src/command.cpp
     src/or.cpp
     src/and.cpp
     src/semicolon.cpp
     unit_tests/unit_test.cpp   
     src/testcommand.cpp
     src/pipe.cpp
     src/input_redirect.cpp
     src/output_redirect_append.cpp 
     src/output_redirect.cpp
     src/parse.cpp
)


TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
