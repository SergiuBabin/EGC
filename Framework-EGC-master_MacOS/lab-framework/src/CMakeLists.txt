# add_subdirectory(engine)
add_subdirectory(hws)
add_subdirectory(labs)
add_subdirectory(playground)

file(GLOB_RECURSE SOURCES engine/*.cpp)
file(GLOB_RECURSE SOURCES_LABS labs/*/*.cpp)
file(GLOB_RECURSE SOURCES_HWS hws/*/*.cpp)

add_executable(main main.cpp ${SOURCES} ${SOURCES_LABS})
add_custom_command(TARGET main POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:main>/res)


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	target_link_libraries(main ${ALL_LIBS} ${LIB_MAC})
else()
	target_link_libraries(main ${ALL_LIBS})
endif()

target_link_libraries(main ${ALL_LIBS} ${LIB_MAC})

set_target_properties(main
    PROPERTIES
    CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_custom_target(run
    COMMAND main
)