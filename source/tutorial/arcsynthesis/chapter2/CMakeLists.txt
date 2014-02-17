
#
# External libraries
#
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)

#
# Includes
#
include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
)
include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/source/glow/include
    ${CMAKE_SOURCE_DIR}/source/glowutils/include
    ${CMAKE_SOURCE_DIR}/source/glowwindow/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#
# Libraries
#
set(
    libs
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
    glow
    glowutils
    glowwindow
)



#
### Build executable of the 2nd chapter, 1st tutorial
#
set(sources FragPosition.cpp)
set(target tutorial2.1)

message(STATUS "OpenGL Tutorial (cf. http://arcsynthesis.org/gltut/index.html): ${target}")

add_executable(${target} ${sources})
target_link_libraries(${target} ${libs})
set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

#
# Deployment
#
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#   LIBRARY DESTINATION ${INSTALL_SHARED}
#   ARCHIVE DESTINATION ${INSTALL_LIB}
)
###



#
### Build executable of the 2nd chapter, 2nd tutorial
#
set(sources VertexColors.cpp)
set(target tutorial2.2)

message(STATUS "OpenGL Tutorial (cf. http://arcsynthesis.org/gltut/index.html): ${target}")

add_executable(${target} ${sources})
target_link_libraries(${target} ${libs})
set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

#
# Deployment
#
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#   LIBRARY DESTINATION ${INSTALL_SHARED}
#   ARCHIVE DESTINATION ${INSTALL_LIB}
)
###




#
### Build executable of the further studies section in the 2nd chapter, 1st tutorial
#
set(sources FragPosition-FurtherStudies.cpp)
set(target further-studies2.1)

message(STATUS "OpenGL Tutorial (cf. http://arcsynthesis.org/gltut/index.html): ${target}")

add_executable(${target} ${sources})
target_link_libraries(${target} ${libs})
set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

#
# Deployment
#
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#   LIBRARY DESTINATION ${INSTALL_SHARED}
#   ARCHIVE DESTINATION ${INSTALL_LIB}
)
###


#
### Build executable of the further studies section in the 2nd chapter, 2nd tutorial
#
set(sources VertexColors-FurtherStudies.cpp)
set(target further-studies2.2)

message(STATUS "OpenGL Tutorial (cf. http://arcsynthesis.org/gltut/index.html): ${target}")

add_executable(${target} ${sources})
target_link_libraries(${target} ${libs})
set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

#
# Deployment
#
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_EXAMPLES}
#   LIBRARY DESTINATION ${INSTALL_SHARED}
#   ARCHIVE DESTINATION ${INSTALL_LIB}
)
###



