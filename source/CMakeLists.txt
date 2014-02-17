# Generate meta-header
configure_file(glow-version.h.in ${CMAKE_CURRENT_BINARY_DIR}/glow-version.h)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Prebuild
add_subdirectory(pre-build)

# Libraries
set(IDE_FOLDER "")
add_subdirectory(glow)
add_subdirectory(glowutils)
add_subdirectory(glowwindow)

# Examples
set(IDE_FOLDER "Examples")
add_subdirectory(examples)

# OpenGL Tutorial with glow (cf. http://arcsynthesis.org/gltut/index.html)
set(IDE_FOLDER "OpenGL Tutorial")
add_subdirectory(tutorial)

# Tests
set(IDE_FOLDER "Tests")
add_subdirectory(tests)
