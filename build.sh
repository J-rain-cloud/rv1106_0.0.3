#!/bin/bash
set -e

TARGET_SOC="rv1106"
# TOOL_CHAIN=/home/ubuntu/rknn/rv1106/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/arm-rockchip830-linux-uclibcgnueabihf/
TOOL_CHAIN=/home/ubuntu/rv1106_sdk_0.0.3/rv1106-0.1/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf
TOOL_CHAIN_LIBS=${TOOL_CHAIN}/arm-rockchip830-linux-uclibcgnueabihf/lib
GCC_COMPILER=${TOOL_CHAIN}/bin/arm-rockchip830-linux-uclibcgnueabihf

export LD_LIBRARY_PATH=${TOOL_CHAIN_LIBS}:$LD_LIBRARY_PATH
export CC=${GCC_COMPILER}-gcc
export CXX=${GCC_COMPILER}-g++

ROOT_PWD=$( cd "$( dirname $0 )" && cd -P "$( dirname "$SOURCE" )" && pwd )

# build
BUILD_DIR=${ROOT_PWD}/build

if [[ ! -d "${BUILD_DIR}" ]]; then
  mkdir -p ${BUILD_DIR}
fi

cd ${BUILD_DIR}
cmake .. -DCOMPILE_FOR_RV1106_IPC=ON \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make -j4
cd -
