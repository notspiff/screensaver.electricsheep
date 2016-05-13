project(screensaver.electricsheep)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(kodi REQUIRED)

include(ExternalProject)

externalproject_add(electricsheep
                    PREFIX electricsheep
                    URL https://github.com/scottdraves/electricsheep/archive/598d93d90573b69559463567540aac8bc8a5b3f3.tar.gz
                    PATCH_COMMAND patch -p1 < ${PROJECT_SOURCE_DIR}/lib/electricsheep/0001-hack-hack-buildsystem-into-building-an-add-on-for-us.patch && 
                    PATCH_COMMAND patch -p1 < ${PROJECT_SOURCE_DIR}/lib/electricsheep/0002-hack-nuiter-window-handling-and-beat-paths-into-subm.patch && 
                    PATCH_COMMAND patch -p1 < ${PROJECT_SOURCE_DIR}/lib/electricsheep/0003-hack-support-newer-ffmpeg.patch WORKING_DIRECTORY <SOURCE_DIR>/client_generic
                    UPDATE_COMMAND cd client_generic && ./autogen.sh
                    CONFIGURE_COMMAND cd <SOURCE_DIR>/client_generic && PKG_CONFIG_PATH=${KODI_BUILD_DIR}/build/lib/pkgconfig ./configure --prefix=<INSTALL_DIR> --disable-static WORKING_DIRECTORY <SOURCE_DIR>/client_generic
                    BUILD_COMMAND make -C client_generic V=0 "CXXFLAGS=\"-I${KODI_INCLUDE_DIR}\" -O3 -std=c++11 -DHAVE_AVC_VID2=1" WORKING_DIRECTORY <SOURCE_DIR>/client_generic
                    INSTALL_COMMAND make -C client_generic install
                    BUILD_IN_SOURCE 1)

set(DEPLIBS electricsheep)
set(SHEEP_CUSTOM_BINARY ${PROJECT_BINARY_DIR}/electricsheep/lib/libscreensheep.so
                        ${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX} electricsheep)
set(SHEEP_CUSTOM_DATA ${PROJECT_BINARY_DIR}/electricsheep/share/electricsheep)

build_addon(screensaver.electricsheep SHEEP DEPLIBS)

include(CPack)
