#ifndef INIT_H
#define INIT_H

typedef unsigned long u32;
typedef unsigned long long u64;
typedef signed long i32;
typedef signed long long i64;
typedef unsigned long uptr;
typedef unsigned long usize;
typedef _Bool bool;

#define NULL ((void *)0)
#define false 0
#define true 1

struct dev_map {
	char *root;
	char *userspace_init;
#ifdef SUPPORT_FSOPTIONS
	char *rootfstype;
	char *rootfsopts;
#endif
#ifdef SUPPORT_LUKS
	bool encrypted_root;
	char *encrypted_root_path;
#endif
};

void handle_cmdline_arg(char *arg, struct dev_map map);
bool contains_word(const char *string, const char *lookword, i32 cc, i32 start);
struct dev_map nullout_dev_map(void);
void print(const char *string);
u32 _strlen(const char *string);
#ifdef SUPPORT_FSOPTIONS
i64 _mount(const char *input, const char *target_dir, char *type, u32 flags, const void *data);
i64 mount(const char *device, const char *dir, char *type, char *flags);
#else
i64 _mount(const char *input, const char *target_dir);
i64 mount(const char *device, const char *dir);
#endif
i64 _mkdir(char *path, unsigned int perms);
i64 _exit(i64 code);
i64 _chdir(char *path);
i64 _chroot(char *path);
i64 _execve(char *path, char *const argv[], char *const envp[]);



#endif
