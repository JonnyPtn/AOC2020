cmake_minimum_required(VERSION 3.10)

project (AOC2020)

# Go through all subfolders
file(GLOB subdirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(dir ${subdirs})
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
    # Add each one, assuming it contains a main.cpp and input.txt
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/main.cpp)
        add_executable(${dir} ${dir}/main.cpp)
        add_custom_command(TARGET ${dir} POST_BUILD COMMENT "Copying input for ${dir}" COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/input.txt $<TARGET_FILE_DIR:${dir}>)

        # Adjust the output dir so each target is in its own folder - otherwise they'll all use the same input.txt
        set_target_properties( ${dir}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${dir}"
        )
    endif()
  endif()
endforeach()