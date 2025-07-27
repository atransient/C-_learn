cmake_minimum_required(VERSION 3.17)

project(C++_learn LANGUAGES CXX CUDA)

add_compile_options(-fPIC)


function(compile_func file_path)
    get_filename_component(filename_only "${file_path}" NAME)
    string(REPLACE ".cpp" "" tar_name ${filename_only})
    add_executable(${tar_name}  ${filename_only})
    target_compile_options(${tar_name} PRIVATE -DNDEBUG -g)
endfunction()


add_subdirectory(std_search)
add_subdirectory(base_search)
add_subdirectory(template_search)