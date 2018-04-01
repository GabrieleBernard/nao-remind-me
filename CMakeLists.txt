cmake_minimum_required(VERSION 3.0)

project(nao-remind-me)

# Configure required libraries ...
if(UNIX) # Darwing or Linux
  find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
  find_package(Threads REQUIRED)
  find_package(OpenSSL 1.0.2 REQUIRED)
  set(OPENSSL_VERSION "1.0.2l")
else()
  message(FATAL_ERROR "-- Unsupported platform sorry! :( ")
endif()

# Configure compiler options ...
message("-- configuring gcc options")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DBOOST_LOG_DYN_LINK")

# Project construction ...
add_executable(agenda-server ./agenda-server/main.cpp)

# headers search paths ...
set(CPPRESTSDK_INCLUDE_DIR "./libs/cpprestsdk/Release/include")
set(MICROSERVICE_INCLUDE_DIR "./agenda-server/foundation/include")
message(MICROSERVICE " ${MICROSERVICE_INCLUDE_DIR}")
set(HEADER_SEARCH_PATHS ${CPPRESTSDK_INCLUDE_DIR} ${MICROSERVICE_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})

# library search paths ...
set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
set(CPPRESTSDK_LIBRARY "${PROJECT_SOURCE_DIR}/libs/cpprestsdk/build.release/Binaries/libcpprest.a")
set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${Boost_LIBRARIES})
message(BOOST_LIBS " ${Boost_LIBRARIES}")
message(OPENSSL_LIBS " ${OPENSSL_LIBRARIES}")
message(CPPRESTSDK_LIBRARY " ${CPPRESTSDK_LIBRARY}")
message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")
include_directories(${HEADER_SEARCH_PATHS})
target_link_libraries(agenda-server ${LIBRARIES_SEARCH_PATHS})
