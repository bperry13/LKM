/**
 * write a LKM for the Linux kernel that displays the following details for all the
 * processes whose PID is greater than an integer given by the user as a module parameter:
 * PROCESS NAME, PID, STATE, PRIORITY, STATIC-PRIORITY, NORMAL-PRIORITY 
 *
 * kernel version 5.13.0-27-generic
 *
 * Completion time: 5 hours
 * 
 * @author Brett Perry
 * @version 1.31.22
 */

#include <linux/sched.h>             
#include <linux/module.h>        
#include <linux/kernel.h>  
#include <linux/tty.h> 


static int input_pid = 0;
module_param(input_pid, int, S_IRUGO | S_IWUSR);


static int PerryLKM_init(void) {
    struct task_struct *task;
    struct task_struct *child;
 
    printk(KERN_INFO "Finding processes with PID > %d \n", input_pid);

    //iterate through all processes
    for_each_process(task){
        //if pid > input_pid then print info
        if(task->pid > input_pid){

            printk(KERN_INFO "%20s%8s%8s%8s%8s%12s\n", "NAME","PID","STATE",
                "PRIO","ST_PRIO", "NORM_PRIO");
            printk(KERN_INFO "%20s\n", "PARENT");
            printk(KERN_INFO "%20s%8d%8ld%8d%8d%12d\n",task->comm,task->pid,
                task->state,task->prio,task->static_prio, task->normal_prio);

            //iterate through all child processes
            for_each_process(child) {
                //if real parent pid == task pid print info
                if(child->real_parent->pid == task->pid){
                    printk(KERN_INFO "%20s\n", "CHILD");
                    printk(KERN_INFO "%20s%8d%8ld%8d%8d%12d\n", child->comm,child->pid,child->state,
                        child->prio,child->static_prio, child->normal_prio);                    
                }                  
            }
            //separator
            printk(KERN_INFO "\n\n");
        }

    }

    return 0;
}

static void PerryLKM_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

module_init( PerryLKM_init );
module_exit( PerryLKM_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LKM to find processes with pid > passed pid from CLI\n");
MODULE_AUTHOR("BRETTPERRY");
