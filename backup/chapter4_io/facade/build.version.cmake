set(AUTO_GEN_MESSAGE "/* File was auto-generated, do not modify! */")
set(ES_MAJOR 0)
set(ES_MINOR 3)

set(VERSION_FILE "${PROJECT_SOURCE_DIR}/build.version")

file(READ  ${VERSION_FILE} ES_BUILD)
math(EXPR ES_BUILD "${ES_BUILD}+1")
file(WRITE ${VERSION_FILE} "${ES_BUILD}")

configure_file (
        "${PROJECT_SOURCE_DIR}/include/es_version.h.in"
        "${PROJECT_BINARY_DIR}/include/generated/es_version.h"
    )
