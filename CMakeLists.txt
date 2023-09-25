cmake_minimum_required(VERSION 3.26)
project(Tarea_1_Paradigmas)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Tarea_1_Paradigmas
        Auto.cpp
        Auto.h
        Camion.cpp
        Camion.h
        Cliente.cpp
        Cliente.h
        json.hpp
        Moto.cpp
        Moto.h
        tarea.cpp
        vehicles.json
        Vehiculo.cpp
        Vehiculo.h
        Venta.h
        Venta.cpp)

add_custom_command(TARGET Tarea_1_Paradigmas POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/vehicles.json
        $<TARGET_FILE_DIR:Tarea_1_Paradigmas>)
