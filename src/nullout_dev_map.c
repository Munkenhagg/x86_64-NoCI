#include "init.h"

struct dev_map nullout_dev_map(void) {
	struct dev_map outmap;
	outmap.root = '\0';
#ifdef SUPPORT_FSOPTIONS
	outmap.rootfstype = '\0';
	outmap.rootfsopts = '\0';
#endif
#ifdef SUPPORT_LUKS
	outmap.encryption = false;
#endif
	return outmap;
}
