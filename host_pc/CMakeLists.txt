CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(test)

add_library(uart STATIC com/uart.c)
add_library(lidar_law STATIC lidar/lidar_law.c)
add_library(tcpip STATIC com/tcpip.c)
add_library(poll STATIC com/poll.c)
add_library(esc_key STATIC teminel_key/esc_key.c)
add_library(argu STATIC argument/argu.c)
add_library(timer STATIC timer/timer.c)
add_library(display STATIC display/display.c)
add_library(cmd STATIC cmd/cmd.c)
add_library(motor STATIC motor/motor.c)
add_library(move STATIC move/move.c)


set(CMAKE_EXE_LINKER_FLAGS "-rdynamic")
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})


ADD_EXECUTABLE(main main.c)

target_link_libraries(  
                        main 
                        uart 
                        tcpip 
                        poll 
                        esc_key
                        argu
                        timer
                        -lrt
                        display
                        lidar_law
                        -lX11
                        -lm
                        cmd
                        motor
                        move
                        ${GTK3_LIBRARIES}
                        -pthread
                     )
