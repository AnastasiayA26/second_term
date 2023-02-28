add_library(include/rational rational.cpp include/rational/rational.h)
set_property(TARGET include/rational PROPERTY CXX_STANDARD 20)
target_include_directories(include/rational PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
install(TARGETS include/rational)