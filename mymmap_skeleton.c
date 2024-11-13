#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h> 
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/slab.h>

static int open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "open\n");
    return 0;
}

static int release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "release\n");
    return 0;
}

static const struct file_operations fops = {
    .open = open,
    .release = release,
};

static int myinit(void)
{int t=register_chrdev(91,"exam",&fops);  // major = 91 car 90=mtd
 if (t<0) printk(KERN_ALERT "registration failed\n");
     else printk(KERN_ALERT "registration success\n");
 return t;
}

static void myexit(void)
{unregister_chrdev(91,"exam");
 printk(KERN_INFO "exit\n");
}

module_init(myinit)
module_exit(myexit)
MODULE_LICENSE("GPL");
