set(SOURCE_TEST Parser.cpp)
set(SOURCE_LIB ParserLib.cpp)

set(PRG_NAME request_test)
set(LIB_NAME Parser)

add_library(${LIB_NAME} STATIC ${SOURCE_LIB})
add_executable(${PRG_NAME} ${SOURCE_TEST})