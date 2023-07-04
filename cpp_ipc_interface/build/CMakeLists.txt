cmake_minimum_required(VERSION 3.13)

project( writer )


find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


add_executable( writer  ../testa.cpp ../cpp_ipc_interface.h )
TARGET_LINK_LIBRARIES( writer  LINK_PUBLIC ${Boost_LIBRARIES} ${Boost_FILESYSTEM_LIBRARY} ${JSONCPP_LIBRARIES})
target_include_directories(writer PUBLIC ${BOOST_INCLUDE_DIR} )

