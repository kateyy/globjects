
#if(OPTION_BUILD_EXAMPLES)

if(WIN32)
    install(FILES ${GLEW_INCLUDE_DIR}/../bin/glew32.dll DESTINATION ${INSTALL_BIN})
endif()

# add the subdirectory that aggregates the sources of arcsynthesis.org tutorial examples implemented with glow
# cf. http://arcsynthesis.org/gltut/index.html for the online tutorial/book
add_subdirectory("arcsynthesis/chapter1")
add_subdirectory("arcsynthesis/chapter2")
add_subdirectory("arcsynthesis/chapter3")
add_subdirectory("arcsynthesis/chapter4")


#endif()
