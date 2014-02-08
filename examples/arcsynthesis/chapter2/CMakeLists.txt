
### The target of the 2nd chapter, 1st tutorial (FragPosition)

set(target-tutorial2.1 tutorial2.1)

message(STATUS "example ${target-tutorial2.1}")

add_executable(${target-tutorial2.1} FragPosition.cpp)

target_link_libraries(${target-tutorial2.1}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-tutorial2.1}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-tutorial2.1}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

###





### The target of the 2nd chapter, 2nd tutorial (VertexColors)

set(target-tutorial2.2 tutorial2.2)

message(STATUS "example ${target-tutorial2.2}")

add_executable(${target-tutorial2.2} VertexColors.cpp)

target_link_libraries(${target-tutorial2.2}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-tutorial2.2}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-tutorial2.2}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

###





### The further studies target of the 2nd chapter, 1st tutorial

set(target-fs2.1 tutorial2_further-studies1)

message(STATUS "example ${target-fs2.1}")

add_executable(${target-fs2.1} FragPosition-FurtherStudies.cpp)

target_link_libraries(${target-fs2.1}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-fs2.1}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-fs2.1}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)





### The further studies target of the 2nd chapter, 2nd tutorial

set(target-fs2.2 tutorial2_further-studies2)

message(STATUS "example ${target-fs2.2}")

add_executable(
    ${target-fs2.2}
    VertexColors-FurtherStudies.cpp
)

target_link_libraries(${target-fs2.2}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-fs2.2}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-fs2.2}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)
