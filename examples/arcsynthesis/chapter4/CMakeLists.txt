
### The main target of the 4th chapter, 1st tutorial


set(target-tutorial4.1 tutorial4.1)

message(STATUS "example ${target-tutorial4.1}")

add_executable(${target-tutorial4.1} OrthoCube.cpp)

target_link_libraries(${target-tutorial4.1}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-tutorial4.1}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-tutorial4.1}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

###






### The main target of the 4th chapter, 2nd tutorial


set(target-tutorial4.2 tutorial4.2)

message(STATUS "example ${target-tutorial4.2}")

add_executable(${target-tutorial4.2} ShaderPerspective.cpp)

target_link_libraries(${target-tutorial4.2}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-tutorial4.2}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-tutorial4.2}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

###





