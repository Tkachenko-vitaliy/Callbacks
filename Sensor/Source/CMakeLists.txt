cmake_minimum_required(VERSION 3.0)

set(project_name Sensor)
set(header_patterns *.h *.hpp)
set(source_patterns *.c *.cc *.cpp *.cxx)
set(configuration Debug)

project(${project_name}) 

set(source_files ./)
set(include_files ../Include)
set(out_dir ../bin)


list(APPEND source_patterns ${header_patterns} ${source_patterns})

macro(enumerate_files_for_humans root_dir patterns output)
  foreach(pattern ${patterns})
    file(GLOB files "${pattern}")
    list(APPEND ${output} ${files})
  endforeach()
endmacro()

enumerate_files_for_humans($(project_name) "${source_patterns}" source_files)
enumerate_files_for_humans($(project_name) "${header_patterns}" header_files)

include_directories(${include_files})
add_library(${project_name} STATIC ${source_files})

set_target_properties(${project_name} PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY ${out_dir})

