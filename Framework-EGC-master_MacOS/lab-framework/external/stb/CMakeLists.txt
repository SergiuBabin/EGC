
SET(GCC_COVERAGE_COMPILE_FLAGS "-fPIC")
set(CMAKE_CXX_STANDARD 11)
set(STB_SOURCE ./stb_vorbis.c)
include_directories(.)

add_library(STB SHARED ${STB_SOURCE})
target_link_libraries(STB ${OPENGL_LIBRARY} ${EXTRA_LIBS})
