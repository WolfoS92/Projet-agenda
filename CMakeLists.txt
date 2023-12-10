cmake_minimum_required(VERSION 3.24)
project(Projet_final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projet_final
        agenda.c
        agenda.h
        cell.c
        cell.h
        complexite.c
        complexite.h
        contact.c
        contact.h
        find.c
        find.h
        list.c
        list.h
        main.c
        menu.c
        menu.h
        timer.c
        timer.h)
