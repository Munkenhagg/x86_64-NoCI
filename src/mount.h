#ifndef MOUNT_H
#define MOUNT_H

#define MS_RDONLY 1
#define MS_NOSUID 2
#define MS_NODEV 4
#define MS_NOEXEC 8
#define MS_SYNCHRONOUS 16
#define MS_REMOUNT 32
#define MS_DIRSYNC 128
#define MS_NOATIME 1024
#define MS_NODIRATIME 2048
#define MS_BIND 4096
#define MS_MOVE 8192
#define MS_REC 16384
#define MS_SILENT 32768
#define MS_RELATIME 2097152
#define MS_STRICTATIME 16777216
#define MS_LAZYTIME 33554432

// yes i used fucking chatgpt to give me thes enumbers because i am NOT googling allat but only for the numbers snd definitions nothing else in this project is ai.



struct kernel_mount_flags_map {
	char *flag_name;
	unsigned long number;
};

#endif
