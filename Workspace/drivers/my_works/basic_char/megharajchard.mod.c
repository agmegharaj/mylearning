#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x885b74e3, "module_layout" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xf4e7c8c5, "cdev_del" },
	{ 0x27cdc719, "cdev_add" },
	{ 0xf7886b99, "cdev_alloc" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xf22449ae, "down_interruptible" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0x25ec1b28, "strlen" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x27e1a049, "printk" },
	{ 0x71e3cecb, "up" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A0ADFB845D8B2D8D1B9EEA4");