cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(flexr_shmq CXX)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_C_FLAGS“$ {CMAKE_C_FLAGS} -fPIC”)
set(CMAKE_CXX_FLAGS“$ {CMAKE_CXX_FLAGS} -fPIC”)

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

# Include cmake modules
include_directories("include")

add_library(flexr_shmq        SHARED flexr_shmq.cc)
add_library(flexr_shmq_static STATIC flexr_shmq.cc)

target_link_libraries(flexr_shmq PRIVATE Threads::Threads)
target_link_libraries(flexr_shmq PRIVATE rt)
target_link_libraries(flexr_shmq_static PRIVATE Threads::Threads)
target_link_libraries(flexr_shmq_static PRIVATE rt)

set_target_properties(flexr_shmq_static PROPERTIES OUTPUT_NAME flexr_shmq)
set_target_properties(flexr_shmq flexr_shmq_static PROPERTIES PUBLIC_HEADER flexr_shmq.h)

configure_file(flexr_shmq.pc.in flexr_shmq.pc @ONLY)


install(TARGETS flexr_shmq flexr_shmq_static
	    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
	    ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/flexr_shmq.pc
	    DESTINATION /usr/local/lib/pkgconfig)

