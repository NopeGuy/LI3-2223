cmake_minimum_required(VERSION 3.21)
project(guiao_3 C)

set(CMAKE_C_STANDARD 99)

include_directories(src)

include(FindPkgConfig)
pkg_check_modules(GLIB glib-2.0 REQUIRED)
include_directories(${GLIB_INCLUDE_DIRS})


add_executable(guiao_3
        src/catalogo-rides.c
        src/catalogo-rides.h
        src/catalogo-drivers.c
        src/catalogo-drivers.h
        src/constructors.c
        src/catalogo.c
        src/constructors.h
        src/main.c
        src/queries.c
        src/queries.h
        src/catalogo-users.c
        src/catalogo-users.h src/main.h src/catalogo.h)


target_link_libraries(${PROJECT_NAME} ${GLIB_LIBRARIES})