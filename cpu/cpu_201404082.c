#include <linux/proc_fs.h>
#include <linux/seq_file.h> 
#include <asm/uaccess.h> 
#include <linux/hugetlb.h>
#include <linux/module.h>       
#include <linux/init.h>
#include <linux/kernel.h>      
#include <linux/fs.h>
#include <linux/sched.h>     
#include <linux/sched/signal.h>  
#include <linux/mm.h>

#define BUFSIZE         150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CPU AND PROCESS");
MODULE_AUTHOR("FERNANDO PAZ");
struct task_struct *task_list;
struct task_struct *task_list_child;
struct list_head *list;

static int escribir_a_proc(struct seq_file * file_proc, void *v) {       

    seq_printf(file_proc, "[");
    for_each_process(task_list) {
            seq_printf(file_proc,"{\"pid\":%d,\"nombre\":\"%s\",\"estado\":%ld,\"ram\":%ld,\"usuario\":%u,\"hijos\":[", task_list->pid,task_list->comm,task_list->state,(task_list->mm != NULL? get_mm_rss(task_list->mm): 0)/1024,(task_list->cred-> uid.val));
            list_for_each(list, &task_list->children){        
                task_list_child = list_entry( list, struct task_struct, sibling );             
                seq_printf(file_proc,"{\"pid\":%d,\"nombre\":\"%s\",\"estado\":%ld,\"ram\":%ld,\"usuario\":%u},",task_list_child->pid, task_list_child->comm, task_list_child->state,(task_list_child->mm != NULL? get_mm_rss(task_list_child->mm): 0)/1024,(task_list_child->cred-> uid.val));
            }
            seq_printf(file_proc, "]},");
    }
    seq_printf(file_proc, "]");
    return 0;
}


static int abrir_aproc(struct inode *inode, struct  file *file) {
  return single_open(file, escribir_a_proc, NULL);
}


static struct file_operations archivo_operaciones =
{    
    .open = abrir_aproc,
    .read = seq_read
};

static int __init cpu_201404082_init(void)
{
    proc_create("cpu_201404082", 0, NULL, &archivo_operaciones);
    printk(KERN_INFO "Hola mundo, Fernando Jose Paz Gonzalez\n");

    return 0;
}
 
static void __exit cpu_201404082_cleanup(void)
{
    remove_proc_entry("cpu_201404082", NULL);    
    printk(KERN_INFO "Diciembre 2021\n");
}


module_init(cpu_201404082_init);
module_exit(cpu_201404082_cleanup); 