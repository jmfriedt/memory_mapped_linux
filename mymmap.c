#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h> /* min */
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/slab.h>

#define len 1024
char *c;

static int mmap(struct file *filp, struct vm_area_struct *vma)
{
// https://static.lwn.net/images/pdf/LDD3/ch15.pdf page 426
// https://linux-kernel-labs.github.io/refs/heads/master/labs/memory_mapping.html
// https://lore.kernel.org/all/062c5218-3370-905a-d113-4d9526d13cd1@microchip.com/T/
// unsigned long pfn = virt_to_phys((void *)c)>>PAGE_SHIFT;
  unsigned long pfn = __pa_symbol((void *)c)>>PAGE_SHIFT;
  int ret=remap_pfn_range(vma, vma->vm_start, pfn, len, vma->vm_page_prot);
  printk(KERN_INFO "mmap %d\n",ret);
  return 0;
}

static int open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "open\n");
// https://litux.nl/mirror/kerneldevelopment/0672327201/ch11lev1sec3.html
// These low-level page functions are useful when you need page-sized chunks of physically contiguous pages, 
// especially if you need exactly a single page or two. For more general byte-sized allocations, the kernel provides kmalloc().
    c = (char *)get_zeroed_page(GFP_KERNEL); // c = kmalloc(len, GFP_KERNEL);
    sprintf(c,"Hello World\n");
    return 0;
}

static int release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "release\n");
    free_page((unsigned long)c);
    return 0;
}

static const struct file_operations fops = {
    .mmap = mmap,
    .open = open,
    .release = release,
};

static int myinit(void)
{int t=register_chrdev(91,"jmf",&fops);  // major = 91 car 90=mtd
 if (t<0) printk(KERN_ALERT "registration failed\n");
    else printk(KERN_ALERT "registration success\n");
 printk(KERN_INFO "Hello\n");
 return t;
}

static void myexit(void)
{unregister_chrdev(91,"jmf");
}

module_init(myinit)
module_exit(myexit)
MODULE_LICENSE("GPL");
