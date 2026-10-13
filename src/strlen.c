#include "init.h"

u32 _strlen(const char *string) {
	u32 i = 0;
	while (string[i] != '\0') {
		i++;
	}
	return i;
}
