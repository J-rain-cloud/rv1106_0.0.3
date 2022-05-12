# Install script for directory: /home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/src/rv1106_ipc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rkipc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rkipc")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rkipc"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/build/src/rv1106_ipc/rkipc")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rkipc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rkipc")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rkipc"
         OLD_RPATH "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/lib/arm-rockchip830-linux-uclibcgnueabihf:/home/ubuntu/rv1106_sdk_0.0.3/rv1106/media/out/lib:/home/ubuntu/rv1106_sdk_0.0.3/rv1106/rknpu2/runtime/RV1106/Linux/librknn_api/armhf:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rkipc")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/src/rv1106_ipc/rkipc-300w.ini")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/src/rv1106_ipc/rkipc-400w.ini")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/src/rv1106_ipc/rkipc-500w.ini")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/src/rv1106_ipc/RkLunch.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/src/rv1106_ipc/RkLunch-stop.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/common/osd/image.bmp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/common/osd/simsun_en.ttf")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/lib/arm-rockchip830-linux-uclibcgnueabihf/libwpa_client.so")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/lib/arm-rockchip830-linux-uclibcgnueabihf/librkmuxer.so")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/lib/arm-rockchip830-linux-uclibcgnueabihf/librkfsmk.so")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/lib/arm-rockchip830-linux-uclibcgnueabihf/libz.so.1")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/lib/arm-rockchip830-linux-uclibcgnueabihf/libz.so")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/lib/arm-rockchip830-linux-uclibcgnueabihf/libiconv.so.2")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/ubuntu/rv1106_sdk_0.0.3/rv1106/project/app/rkipc/git_rkipc_0.0.3/lib/arm-rockchip830-linux-uclibcgnueabihf/libiconv.so")
endif()

