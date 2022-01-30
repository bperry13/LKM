/**
 * write a LKM for the Linux kernel that displays the following details for all the
 * processes whose PID is greater than an integer given by the user as a module parameter:
 * PROCESS NAME, PID, STATE, PRIORITY, STATIC-PRIORITY, NORMAL-PRIORITY 
 *
 * kernel version 5.11.0-46-generic
 *
 * Completion time: 3 hours
 * //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
 * @author Brett Perry
 * @version 1.31.22
 */

#include <linux/init.h>
#include <linux/module.h>  
#include <linux/kernel.h> 


static int PerryLKM_init(void) 
{
	printk(KERN_INFO "Loading Module\n");
  
	return 0;
}

static void PerryLKM_exit(void) 
{
	printk(KERN_INFO "Removing Module\n");
}

module_init( PerryLKM_init );
module_exit( PerryLKM_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LKM");
MODULE_AUTHOR("BRETTPERRY");
