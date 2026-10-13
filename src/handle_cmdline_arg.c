#include "init.h"

void handle_cmdline_arg(char *arg, struct dev_map map) {
	if (arg == NULL || arg[0] == '\0') {
		return;
	}
	if (map.root == NULL) {
		if (contains_word(arg, "root=", 5, -1)) {
			map.root = arg + 5;
			return;
		}
	}
	if (map.userspace_init == NULL) {
		if (contains_word(arg, "userspace_init=", 15, -1)) {
			map.userspace_init = arg + 15;
		}
	}
#ifdef SUPPORT_FSOPTIONS
	if (map.rootfstype == NULL) {
		if (contains_word(arg, "rootfs=", 7, -1)) {
			map.rootfstype = arg + 7;
			return;
		}
	}

	if (map.rootfsopts == NULL) {
		if (contains_word(arg, "rootfsopts=", 11, -1)) {
			map.rootfsopts = arg + 11;
			return;
		}
	}
#endif
#ifdef SUPPORT_LUKS
	if (contains_word(arg, "encrypted", 9, -1) && _strlen(arg) == 9) { // we have no fucking strcmp so i will just use this functions
		map.encrypted_root = true;
	}
#endif


	return;
}
