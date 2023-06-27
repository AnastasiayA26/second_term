cmake_minimum_required(VERSION 3.23)
project(filter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")
set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file" -G Ninja)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

# Set the vcpkg triplet
set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")

find_package(OpenCV REQUIRED COMPONENTS core highgui imgcodecs imgproc videoio)
include_directories(${OpenCV_INCLUDE_DIRS})

if(WIN32)
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../bin")
else()
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../lib")
endif()

add_subdirectory(filter)
add_subdirectory(prj.test)
add_subdirectory(ctikz)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc)
    add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

add_custom_target(build_all
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
        DEPENDS filter prj.test ctikz
        COMMENT "Building all targets..."
        )

if(NIBLACK_GENERATE_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(NIBLACK_DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(NIBLACK_DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)
        configure_file(${NIBLACK_DOXYGEN_IN} ${NIBLACK_DOXYGEN_OUT})
        add_custom_target(niblack_docs_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${NIBLACK_DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
        install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
                DESTINATION ./)
    else()
        message(STATUS "Couldn't find Doxygen")
    endif()
endif()

install(TARGETS filter DESTINATION bin)
install(DIRECTORY filter/include/ DESTINATION include/filter)
install(FILES filter/src/filter.cpp DESTINATION filter/src)

install(DIRECTORY prj.test/ DESTINATION bin/prj.test)
install(FILES prj.test/test.cpp DESTINATION bin/prj.test)
install(FILES prj.test/CMakeLists.txt DESTINATION bin/prj.test)

install(TARGETS ctikz DESTINATION bin)
install(DIRECTORY ctikz/include/ DESTINATION include/ctikz)
install(FILES ctikz/ctikz.cpp ctikz/include/ctikz/ctikz.hpp DESTINATION include/ctikz)

if(NIBLACK_INSTALL_TARGET)
    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*opencv_core*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*opencv_highgui4.dll*"
            )
    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*libwebpdecoder*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*opencv_core4*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*opencv_imgcodecs4*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*opencv_imgcodecs4*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*opencv_imgproc4*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*jpeg62*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*opencv_videoio4*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*zlib1*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*libwebp*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*libpng16*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*tiff*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*libsharpyuv*"
            )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
            DESTINATION bin
            FILES_MATCHING PATTERN "*liblzma*"
            )

endif()

# Install CMakeLists.txt files
install(FILES CMakeLists.txt DESTINATION .)
install(FILES filter/CMakeLists.txt DESTINATION filter)
install(FILES prj.test/CMakeLists.txt DESTINATION prj.test)
install(FILES ctikz/CMakeLists.txt DESTINATION ctikz)



       








