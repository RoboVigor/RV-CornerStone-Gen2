cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(CornerStone_Gen2 STATIC)

file(GLOB_RECURSE src
     "${CMAKE_CURRENT_LIST_DIR}/Peripheral/Src/*.cpp"
     "${CMAKE_CURRENT_LIST_DIR}/Protocol/Src/*.cpp"
     "${CMAKE_CURRENT_LIST_DIR}/Core/Src/*.cpp")
target_sources(CornerStone_Gen2 PRIVATE
               ${src}
               )

target_include_directories(CornerStone_Gen2 PUBLIC
                           ${CMAKE_CURRENT_LIST_DIR}/Peripheral/Inc
                           ${CMAKE_CURRENT_LIST_DIR}/Protocol/Inc
                            ${CMAKE_CURRENT_LIST_DIR}/Core/Inc)

target_link_libraries(CornerStone_Gen2 PUBLIC
                      stm32cubemx)