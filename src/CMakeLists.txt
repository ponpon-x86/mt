file(GLOB_RECURSE SOURCES *.cpp)

add_executable(mt ${SOURCES})

target_include_directories(mt PUBLIC ../include)
