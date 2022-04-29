cmake_minimum_required(VERSION 3.1)

project(learning_behaviour-tree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_tutorial01 ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial01/tutorial01.cpp)

# REFERENCE: https://www.youtube.com/watch?v=ED-WUk440qc&list=PLalVdRk2RC6o5GHu618ARWh0VO0bFlif4&index=3
# DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed ${GIT_SUBMOD_RESULT}, please check")
        endif()
    endif()
endif()

# CHECK ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdparty/behaviortree_cpp_v3/CMakeLists.txt")
    message(FATAL_ERROR "The googletest submodule was not downloaded! GIT_SUBMODULE was turned off or failed!")
endif()

add_subdirectory(thirdparty/behaviortree_cpp_v3)

target_link_libraries(${PROJECT_NAME}_tutorial01 behaviortree_cpp_v3)
