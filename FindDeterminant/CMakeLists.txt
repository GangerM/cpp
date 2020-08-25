cmake_minimum_required(VERSION 3.13)
project(FindDeterminant LANGUAGES C)

add_compile_options(-Wall -Werror)


#these are the source files that make up your project
set (SOURCES main.c matrix.c matrix.h) #add any other sources you have after matrix.h

#create the executable from the sources
add_executable(FindDeterminant ${SOURCES}) 
target_compile_options(FindDeterminant PRIVATE -Wall -Werror)

#name the executable
set_target_properties(FindDeterminant
        PROPERTIES
        OUTPUT_NAME "FindDeterminant"
        SUFFIX ".out")