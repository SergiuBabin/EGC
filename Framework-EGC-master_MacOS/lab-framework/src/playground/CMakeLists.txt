add_executable(playground playground.cpp)

target_link_libraries(playground ${ALL_LIBS})

set_target_properties(playground
    PROPERTIES
    CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_custom_target(run_playground
    COMMAND playground    
)