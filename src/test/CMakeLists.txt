#add_library(Test main_test.cpp)

#Exectuable
add_executable(VDSProject_test main_test.cpp)
target_link_libraries(VDSProject_test Manager gtest gtest_main pthread)
