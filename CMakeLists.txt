cmake_minimum_required(VERSION 3.21)
project(guiao_3 C)

set(CMAKE_C_STANDARD 99)

include_directories(src)

include(FindPkgConfig)
pkg_check_modules(GLIB glib-2.0 REQUIRED)
include_directories(${GLIB_INCLUDE_DIRS})


add_executable(guiao_3
        src/catalogo-rides.c
        includes/catalogo-rides.h
        src/catalogo-drivers.c
        includes/catalogo-drivers.h
        src/constructors.c
        src/catalogo.c
        includes/constructors.h
        src/main.c
        src/queries.c
        includes/queries.h
        src/catalogo-users.c
        includes/catalogo-users.h includes/main.h includes/catalogo.h)


target_link_libraries(${PROJECT_NAME} ${GLIB_LIBRARIES})