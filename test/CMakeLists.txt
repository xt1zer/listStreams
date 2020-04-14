add_executable(${CMAKE_PROJECT_NAME}_test testMain.cpp listTest.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_test gtest gtest_main pthread)