set(LIB_SOURCE_FILES
        ${LIB_SOURCE_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/number.cpp
        )

set(LIB_HEADER_FILES
        ${LIB_HEADER_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/number.hpp
        )

add_library(lib${CMAKE_PROJECT_NAME}
        SHARED
        ${LIB_SOURCE_FILES}
        ${LIB_HEADER_FILES}
        )
