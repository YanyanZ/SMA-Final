set(SERVER_NAME gameServer)
set(SOURCES Player.cpp)

add_executable(${SERVER_NAME} ${SOURCES})

target_link_libraries(${SERVER_NAME} ${Boost_LIBRARIES})
target_link_libraries(${SERVER_NAME} Parser)
