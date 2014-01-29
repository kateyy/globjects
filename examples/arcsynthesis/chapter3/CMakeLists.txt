
### The target of the 3rd chapter, 1st tutorial (CPUPositionOffset)

set(target-tutorial3.1 tutorial3.1)

message(STATUS "example ${target-tutorial3.1}")

add_executable(${target-tutorial3.1} CPUPositionOffset.cpp)

target_link_libraries(${target-tutorial3.1}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-tutorial3.1}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-tutorial3.1}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

###





### The target of the 3rd chapter, 2nd tutorial (VertPositionOffset)

set(target-tutorial3.2 tutorial3.2)

message(STATUS "example ${target-tutorial3.2}")

add_executable(${target-tutorial3.2} VertPositionOffset.cpp)

target_link_libraries(${target-tutorial3.2}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-tutorial3.2}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-tutorial3.2}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

###





### The target of the 3rd chapter, 3rd tutorial (VertCalcOffset)

set(target-tutorial3.3 tutorial3.3)

message(STATUS "example ${target-tutorial3.3}")

add_executable(${target-tutorial3.3} VertCalcOffset.cpp)

target_link_libraries(${target-tutorial3.3}
    ${GLEW_LIBRARIES}
    glow
    glowutils
    glowwindow
    ${EXAMPLE_COMMON}
)

set_target_properties(${target-tutorial3.3}
    PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${GLOW_EXAMPLES_FOLDER}
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

install(TARGETS ${target-tutorial3.3}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#    LIBRARY DESTINATION ${INSTALL_SHARED}
#    ARCHIVE DESTINATION ${INSTALL_LIB}
)

###





### The further studies target of the 2nd chapter, 1st tutorial

#set(target-fs3.1 tutorial3.1-further-studies)

#message(STATUS "example ${target-fs3.1}")

#add_executable(${target-fs3.1} FragPosition-FurtherStudies.cpp)

#target_link_libraries(${target-fs3.1}
#    ${GLEW_LIBRARIES}
#    glow
#    glowutils
#    glowwindow
#    ${EXAMPLE_COMMON}
#)

#set_target_properties(${target-fs3.1}
#    PROPERTIES
#    LINKER_LANGUAGE CXX
#    FOLDER ${GLOW_EXAMPLES_FOLDER}
#    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
#    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
#    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
#    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
#    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
#    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

#install(TARGETS ${target-fs3.1}
#    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
##    LIBRARY DESTINATION ${INSTALL_SHARED}
##    ARCHIVE DESTINATION ${INSTALL_LIB}
#)
