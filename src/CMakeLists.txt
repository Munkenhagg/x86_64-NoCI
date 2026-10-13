cmake_minimum_required(VERSION 3.16)

project(x86_64-NoC-Initramfs C ASM_NASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

option(_SUPPORT_FSOPTIONS "Allows for root filesystem optins to be set via the commandline, using 'rootfs=...' and 'rootfsopts=...'" ON)
option(_SUPPORT_LUKS "Allows for unencrypting a luks-encrypted root properly" ON)
option(_SUPPORT_LVM "Allows for a LVM filesystem to be used")

add_executable(init
	init.c contains_word.c handle_cmdline_arg.c strlen.c mount.c print.c nullout_dev_map.c
	asm/mount.asm asm/mkdir.asm asm/chdir.asm asm/chroot.asm asm/execve.asm asm/exit.asm
)

if(_SUPPORT_FSOPTIONS)
	target_compile_definitions(init PRIVATE SUPPORT_FSOPTIONS)
endif()
if(_SUPPORT_LUKS)
	target_compile_definitions(init PRIVATE SUPPORT_LUKS)
endif()
if(_SUPPORT_LVM)
	target_compile_definitions(init PRIVATE SUPPORT_LVM)
endif()

target_compile_options(init PRIVATE
	$<$<COMPILE_LANGUAGE:C>:-ffreestanding>
	$<$<COMPILE_LANGUAGE:C>:-fno-builtin>
	$<$<COMPILE_LANGUAGE:C>:-fno-stack-protector>
	$<$<COMPILE_LANGUAGE:C>:-fno-pie>
)

target_link_options(init PRIVATE
	-nostdlib
	-static
	-no-pie
	-Wl,-e,_start
	-Wl,--build-id=none
)
