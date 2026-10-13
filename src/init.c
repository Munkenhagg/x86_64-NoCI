#include "init.h"
#include "mount.h"

__attribute__((noreturn)) void _start(void) {
	print("x86_64-NoCI - initramfs");
#ifdef DEBUG_INFO
	print("Attributes: ");
#ifdef SUPPORT_LUKS
	print("LUKS/LUKS2");
#endif
#ifdef SUPPORT_FSOPTIONS
	print("FSOPTIONS");
#endif
#ifdef SUPPORT_LVM
	print("LVM/LVM2");
#endif
	print("\n");
#endif
	print("<i> Starting stack using asm...");
	uptr *stack;
	__asm__ volatile (
	"mov %%rsp, %0"
	: "=r"(stack)
	);
	u32 argc = (u32)stack[0];
	char **argv = (char **)&stack[1];
	print("<i> Reading command line...\n");
	struct dev_map device_map = nullout_dev_map();
	for (u32 i = 0; i < argc; i++) {
		char *carg = argv[i];
		handle_cmdline_arg(carg, device_map);
	}
	_mkdir("/newroot", 0755);
#ifdef SUPPORT_FSOPTIONS
	i64 return_code = mount(device_map.root, "/newroot", device_map.rootfstype, device_map.rootfsopts);
#else
	i64 return_code = mount(device_map.root, "/newroot");
#endif
	if (return_code != 0) {
		print("<!> root mount failed!\n");
		print("x86_64-NoCI debug info:\n");
		print("Reason: mount syscall or freestanding mount implementation returned a non-zero value\n");
		print("cmdline: ");
		for (u32 i = 0; i < argc; i++) {
			print(argv[i]);
		}
		print("\ndevice map struct:\n");
		print("device_map\n");
		print("\t.root: ");
		print(device_map.root);
		print("\n");
#ifdef SUPPORT_FSOPTIONS
		print("\t.rootfstype: ");
		print(device_map.rootfstype);
		print("\n\t.rootfsopts: ");
		print(device_map.rootfsopts);
		print("\n");
#endif
#ifdef SUPPORT_LUKS
		print("\t.encrypted_root: ");
		if (device_map.encrypted_root) {
			print("true");
		} else {
			print("false");
		}
		print("\t.encrypted_root_path: ");
		print(device_map.encrypted_root_path);
		print("\n");
#endif
		_exit(-1);
	}
	print("<i> Root mount successful\n");
	print("<i> Moving root to /newroot...");
	return_code = mount("/newroot", "/", NULL, "move");
	if (return_code != 0) {
		print("<!> Moving root to /newroot failed!");
		print("x86_64-NoCI debug info:\n");
		print("error code (as char): ");
		print("0x");
		print((char *)return_code);
		print("\n");
		_exit(-1);
	}
	return_code = _chdir("/");
	if (return_code != 0) {
		print("<!> Changing process directory to new '/' failed!");
		print("x86_64-NoCI debug info:\n");
		print("error code (as char): ");
		print("0x");
		print((char *)return_code);
		print("\n");
		_exit(-1);
	}
	_chroot(".");
	char **envp;
	if (device_map.userspace_init) {
		_execve(device_map.userspace_init, argv, envp);
	}
	print("<?> Userspace init was passed through command line, but failed to execute due to permissions or it simply does not exist. Was this meant to happen?");
	_execve("/sbin/init", argv, envp);
	_execve("/bin/init", argv, envp);
	print("<!> No userspace init could not be found!!!");
	print("<!> Initramfs Init exiting intentionally, may trigger kernel panic.");
	_exit(-1);
	__builtin_unreachable();
}

