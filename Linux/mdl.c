#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

MODULE_DESCRIPTION("Kernel Leaking Memory module");
MODULE_LICENSE("GPL");

static int sample_module_drv_probe(struct device *dev)
{
    printk(KERN_DEBUG "probe kernel leaking memory module device\n");
    return 0;
}

static int sample_module_drv_remove(struct device *dev)
{
    printk(KERN_DEBUG "remove kernel leaking memory device\n");
    return 0;
}

static struct device_driver sample_module_driver = {
    .name           = "Leaking_memory",
    .bus            = &platform_bus_type,
    .probe          = sample_module_drv_probe,
    .remove         = sample_module_drv_remove,
};

static int __init sample_module_init(void)
{
   int bytesLeaked =  128000;
   char *var = kmalloc(bytesLeaked, GFP_KERNEL);

   if(var != NULL)
   {
     printk("leaked %d bytes at address %x\n", bytesLeaked, (unsigned int)var);
   }

    var = NULL;
    printk(KERN_DEBUG "init Leaking memory module device\n");
    return driver_register(&sample_module_driver);
}

static void __exit sample_module_cleanup(void)
{
    printk(KERN_DEBUG "cleanup Leaking memory module device\n");
    driver_unregister(&sample_module_driver);
}

module_init(sample_module_init);
module_exit(sample_module_cleanup);