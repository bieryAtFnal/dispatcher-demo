cmake_minimum_required(VERSION 3.12)
project(dispatcherdemo VERSION 1.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../daq-buildtools/cmake ${CMAKE_MODULE_PATH})
include(DAQ)

daq_setup_environment()

find_package(appfwk REQUIRED)

##############################################################################
daq_point_build_to( src )

add_library(dispatcherdemo_DataPackager_duneDAQModule src/DataPackager.cpp)
target_link_libraries(dispatcherdemo_DataPackager_duneDAQModule appfwk::appfwk)

##############################################################################
daq_point_build_to( test )

file(COPY test/data_packager_demo.json DESTINATION test)

daq_install(TARGETS dispatcherdemo_DataPackager_duneDAQModule )
