file(GLOB CPP_SOURCE_FILES "*.cpp")
message(STATUS "CPP_SOURCE_FILES: ${CPP_SOURCE_FILES}")

foreach(file_path IN LISTS CPP_SOURCE_FILES)
    compile_func(${file_path})
endforeach()
