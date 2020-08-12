cmake_minimum_required(VERSION 3.17)
project(WakeOnLanIPTime)

set(CMAKE_CXX_STANDARD 14)

if (APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    set(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")
else()
    set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)
    set(CMAKE_C_COMPILER o64-clang)
    set(CMAKE_CXX_COMPILER o64-clang++)
endif()

find_package(cpprestsdk REQUIRED)
find_package (OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(WakeOnLanIPTime main.cpp jsoncpp.cpp json.h)

TARGET_LINK_LIBRARIES( WakeOnLanIPTime PRIVATE cpprestsdk::cpprest OpenSSL::SSL Boost::system OpenSSL::Crypto)