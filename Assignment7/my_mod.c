///my_mod.c
#include<linux/init.h>

#include<linux/module.h>

#include<linux/sched.h>

MODULE_LICENSE("GPL");
static int test_init(void) {
    printk(KERN_CRIT "my_mod is loaded...\n");
    struct task_struct * task;
    for_each_process(task) {
        printk("Process Name :%s\t PID:%d\t Process state:%ld\n", task->comm, task->pid, task->state);
    }
    return 0;
}
static void test_exit(void) {
    printk(KERN_INFO "Clearing up.\n");
}
module_init(test_init);
module_exit(test_exit);
