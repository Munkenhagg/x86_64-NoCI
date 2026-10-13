#!/bin/env sh

cd "$(dirname "$0")/.."

if ! command -v cmake > /dev/null 2>&1; then
	echo "CMake not installed, please install it before running this script."
	exit 1
fi

if [ "$(uname -m)" != "x86_64" ] && [ "$(uname -m)" != amd64 ]; then
	echo "Non-x86_64 machine detected! build will fail on all architectures excelt x86_64, AKA amd64"
	exit 1
fi
OUT="../x86_64-NoCI.img"

echo "Starting build"
mkdir -p build
cd build
cmake $@ ..
cmake --build . --parallel "$(nproc)"
echo "Build complete, starting packaging process"
cd ..
mkdir -p tree
cp build/init tree/init
cd tree
mkdir -p bin
find . -print0 | cpio --null -o -H newc > "$OUT"
cd ..
rm -rf build tree
echo "Packaging complete successfully"
echo "Output file: $(realpath "$OUT")"
