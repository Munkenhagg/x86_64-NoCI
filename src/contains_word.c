#include "init.h"

bool contains_word(const char *string, const char *lookword, i32 cc, i32 start) {
	u32 c = (start < 0) ? 0 : (u32)start;
	cc = (cc < 0) ? _strlen(lookword) : cc;
	for (u32 i = 0; i < cc; i++) {
		if (string[c + i] == '\0' || string[c + i] != lookword[i]) {
			return false;
		}
	}
	return true;
}
