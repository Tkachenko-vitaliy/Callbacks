cmake_minimum_required(VERSION 3.0)

set(project_name SensorTest)
set(header_patterns *.h *.hpp)
set(source_patterns *.c *.cc *.cpp *.cxx)
set(configuration Debug)
set(dependancy_lib Sensor SensorApi)

project(${project_name}) 

set(source_files ./)
set(include_files ../Include)
set(out_dir ../bin)

include_directories(${include_files})
link_directories(${out_dir})

list(APPEND source_patterns ${header_patterns} ${source_patterns})

macro(enumerate_files_for_humans root_dir patterns output)
  foreach(pattern ${patterns})
    file(GLOB files "${pattern}")
    list(APPEND ${output} ${files})
  endforeach()
endmacro()

enumerate_files_for_humans($(project_name) "${source_patterns}" source_files)
enumerate_files_for_humans($(project_name) "${header_patterns}" header_files)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread")

add_executable(${project_name} ${source_files})
target_link_libraries(${project_name} ${dependancy_lib})

set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${out_dir})

