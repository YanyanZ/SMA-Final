set(CLIENT_NAME clientRef)
set(SERVER_NAME serverRef)
set(CSOURCES Client.cpp)
set(SSOURCES Server.cpp)

add_executable(${CLIENT_NAME} ${CSOURCES})
add_executable(${SERVER_NAME} ${SSOURCES})

target_link_libraries(${CLIENT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${SERVER_NAME} ${Boost_LIBRARIES})