cmake_minimum_required(VERSION 3.5.0)
project(RTChallenge
        VERSION 0.1.0
        LANGUAGES C CXX)

set(BIN_DIR "${PROJECT_SOURCE_DIR}/bin/")

# LibSDL2
# =======
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/lib/SDL2/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Project build targets
# =====================
add_executable(UNIT_TEST1 src/tests/test_001-a.cpp)
add_executable(UNIT_TEST2 src/tests/test_001-b.cpp)
add_executable(SDL_TEST src/tests/test_002-b.cpp)

# Project libraries
# =================
add_subdirectory(src/lib)

target_link_libraries(UNIT_TEST1 PUBLIC
                      RT_Datatypes)

target_link_libraries(UNIT_TEST2 PUBLIC
                        RT_Datatypes)

target_link_libraries(SDL_TEST PUBLIC
                      ${SDL2_LIBRARIES}
                      RT_Datatypes)


# Move builds to the bin
# ======================
add_custom_command(TARGET SDL_TEST POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL_TEST> ${BIN_DIR}/SDL_TEST.exe
                   COMMENT "Created ${PROJECT_SOURCE_DIR}/bin/SDL_TEST.exe")

# Collect required DLLs to bin
# ============================
add_custom_command(TARGET SDL_TEST POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SDL_TEST> ${BIN_DIR}
                   COMMAND_EXPAND_LISTS
                   )

#include(CTest)
enable_testing()

