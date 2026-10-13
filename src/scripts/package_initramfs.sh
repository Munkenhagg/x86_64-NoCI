#!/bin/env sh

cd "$(dirname "$0")/.."

if ! command -v cmake > /dev/null 2>&1; then
	echo "CMake not installed, please install it before running this script."
	exit 1
fi

if [ "$(uname -m)" != "x86_64" ] || [ "$(uname -m)" != amd64 ]; then
	echo "Non-x86_64 machine detected! build will fail on all architectures excelt x86_64, AKA amd64"
	exit 1
fi
echo "Starting build"
mkdir build
cd build
cmake ..
cmake --build . --parallel "$(nproc)"
echo "Build complete, starting packaging process"
cd ..
mkdir tree
cp init tree/init
cd tree
mkdir bin
find . -print0 | cpio --null -o -H newc > ../x86_64-NoCI.img
