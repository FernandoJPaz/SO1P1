#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/sysinfo.h>
#include <linux/uaccess.h>


static int my_proc_show(struct seq_file *m, void *v) {
    long memoria_total = 0;
    long memoria_libre = 0;
    long memoria_usada = 0;
    
    struct sysinfo si;
    si_meminfo(&si);

    memoria_total = (si.totalram * 4);
    memoria_libre = (si.freeram * 4);
    memoria_usada = memoria_total - memoria_libre;
    seq_printf(m, "{\"ram_total\": %8lu", (memoria_total));
    seq_printf(m, ", \"ram_free\": %8lu", (memoria_libre));
    seq_printf(m, ", \"ram_usage\": %8lu", (memoria_usada));

    seq_printf(m, ", \"ram_usage_percent\":%8lu }", (memoria_usada*100/memoria_total));
    return 0;
}

static ssize_t my_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos) {
    return 0;
}

static int my_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, my_proc_show, NULL);
}

static struct file_operations my_fops={
    .owner = THIS_MODULE,
    .open = my_proc_open,
    .release = single_release,
    .read = seq_read,
    .llseek = seq_lseek,
    .write = my_proc_write
};

static int __init test_init(void) {
    struct proc_dir_entry *entry;
    entry = proc_create("memo_201404082", 0777, NULL, &my_fops);
    if(!entry) {
	printk(KERN_INFO "adios_201404082");
        return -1;
    } else {
        printk(KERN_INFO "Hola mundo, 201404082\n");
    }
    return 0;
}

static void __exit test_exit(void) {
    remove_proc_entry("memo_201404082", NULL);
    printk(KERN_INFO "Sistemas operativos 1 \n");
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fernando Paz");
MODULE_DESCRIPTION("Muestra el porcentaje de Memoria utilizada");