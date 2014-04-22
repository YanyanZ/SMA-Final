set(CLIENT_NAME clientTest)
set(SOURCES Client.cpp Player.cpp)

add_executable(${CLIENT_NAME} ${SOURCES})

target_link_libraries(${CLIENT_NAME} ${Boost_LIBRARIES})