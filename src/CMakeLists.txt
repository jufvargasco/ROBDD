
add_subdirectory(test)
add_subdirectory(bench)
add_subdirectory(verify)
add_subdirectory(reachable)


add_library(Manager Manager.cpp ManagerInterface.cpp murmurhash.h)

