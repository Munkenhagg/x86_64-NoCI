#include "init.h"

static inline long syscall3(long nr, long a, long b, long c) {
	long ret;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "a"(nr), "D"(a), "S"(b), "d"(c)
		: "rcx", "r11", "memory"
	);
	return ret;
}

void print(const char *string) {
	usize length = strlen(string);
	syscall3(1, 1, (long)string, (long)length);
}
