cmake_minimum_required(VERSION 3.1)

project(learningBehaviourTree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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


# Tutorial 01
list(APPEND Tutorial01Sources
    Tutorial01/tutorial01.cpp
    Tutorial01/tutorial01_nodes.cpp
)
# Need to install or copy the xml file to the correct directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial01/tutorial01_tree.xml DESTINATION ${CMAKE_BINARY_DIR})
add_executable(tutorial01 ${Tutorial01Sources})
target_link_libraries(tutorial01 behaviortree_cpp_v3)
target_include_directories(tutorial01 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial01)

# Tutorial 02
list(APPEND Tutorial02Sources
    Tutorial02/tutorial02.cpp
    Tutorial02/tutorial02_nodes.cpp
)
# Need to install or copy the xml file to the correct directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial02/tutorial02_tree.xml DESTINATION ${CMAKE_BINARY_DIR})
add_executable(tutorial02 ${Tutorial02Sources})
target_link_libraries(tutorial02 behaviortree_cpp_v3)
target_include_directories(tutorial02 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial02)

# Tutorial 03
list(APPEND Tutorial03Sources
    Tutorial03/tutorial03.cpp
    Tutorial03/tutorial03_nodes.cpp
)
add_executable(tutorial03 ${Tutorial03Sources})
target_link_libraries(tutorial03 behaviortree_cpp_v3)
target_include_directories(tutorial03 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial03)

# Tutorial 04
list(APPEND Tutorial04Sources
    Tutorial04/tutorial04.cpp
    Tutorial04/tutorial04_nodes.cpp
)
add_executable(tutorial04 ${Tutorial04Sources})
target_link_libraries(tutorial04 behaviortree_cpp_v3)
target_include_directories(tutorial04 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial04)

# Tutorial 06
list(APPEND Tutorial05Sources
    Tutorial05/tutorial05.cpp
    Tutorial05/tutorial05_nodes.cpp
)
add_executable(tutorial05 ${Tutorial05Sources})
target_link_libraries(tutorial05 behaviortree_cpp_v3)
target_include_directories(tutorial05 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial05)

# Tutorial 06
list(APPEND Tutorial06Sources
    Tutorial06/tutorial06.cpp
    Tutorial06/tutorial06_nodes.cpp
)
add_executable(tutorial06 ${Tutorial06Sources})
target_link_libraries(tutorial06 behaviortree_cpp_v3)
target_include_directories(tutorial06 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial06)

# Tutorial 07
list(APPEND Tutorial07Sources
    Tutorial07/tutorial07.cpp
    Tutorial07/myLegacyCode.cpp
)
add_executable(tutorial07 ${Tutorial07Sources})
target_link_libraries(tutorial07 behaviortree_cpp_v3)
target_include_directories(tutorial07 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tutorial07)