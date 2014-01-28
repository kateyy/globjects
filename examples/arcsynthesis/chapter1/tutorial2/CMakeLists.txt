
### The target of the 1st chapter, tutorial 2.1 (FragPosition)

set(target-tutorial2.1 chapter1-tutorial2.1)

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





### The target of the 1st chapter, tutorial 2.2 (VertexColors)

set(target-tutorial2.2 chapter1-tutorial2.2)

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





### The further studies target of the 1st chapter, 2nd tutorial

set(target-further-studies-2.1 chapter1-tutorial2.1-further-studies)

message(STATUS "example ${target-further-studies-2.1}")

add_executable(
    ${target-further-studies-2.1}
    FragPosition-FurtherStudies.cpp
)

target_link_libraries(${target-further-studies-2.1}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-further-studies-2.1}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-further-studies-2.1}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)
