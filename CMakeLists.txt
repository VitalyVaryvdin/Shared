cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(Reversing)

Set_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(System)
add_subdirectory(Examples/Flate)
add_subdirectory(Examples/Template)

Set_PROPERTY(TARGET System	    PROPERTY FOLDER "Libraries")
Set_PROPERTY(TARGET Flate	    PROPERTY FOLDER "Examples")
Set_PROPERTY(TARGET Template	PROPERTY FOLDER "Examples")