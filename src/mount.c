#include "init.h"
#include "mount.h"

#ifdef SUPPORT_FSOPTIONS

static const struct kernel_mount_flags_map fs_flag_map[] = {
{ "ro", MS_RDONLY },
{ "nosuid", MS_NOSUID },
{ "nodev", MS_NODEV },
{ "noexec", MS_NOEXEC },
{ "sync", MS_SYNCHRONOUS },
{ "remount", MS_REMOUNT },
{ "dirsync", MS_DIRSYNC },
{ "noatime", MS_NOATIME },
{ "nodiratime", MS_NODIRATIME },
{ "bind", MS_BIND },
{ "move", MS_MOVE },
{ "silent", MS_SILENT },
{ "relatime", MS_RELATIME },
{ "strictatime", MS_STRICTATIME },
{ "lazytime", MS_LAZYTIME }
};

i64 mount(const char *device, const char *dir, char *type, char *flags)
#else
i64 mount(const char *device, const char *dir)
#endif
{
#ifdef SUPPORT_FSOPTIONS
	u32 bmflags;
	for (u32 i = 0; i < 15; i++) {
		if (contains_word(flags, fs_flag_map[i].flag_name, -1, -1)) {
			bmflags |= fs_flag_map[i].number;
		}
	}
#endif
#ifdef SUPPORT_FSOPTIONS
	return _mount(device, dir, type, bmflags, flags);
#else
	return _mount(device, dir);
#endif
}
