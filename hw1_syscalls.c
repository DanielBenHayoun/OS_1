#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>

int sys_enable_policy(pid_t pid, int size, int password){
	int res;
	
	//parameters tests
	if(pid<0){
		res = -ESRCH;
		printk("bad pid %d error_num %d\n",pid , res);
		return res;
	}
	task_t* task = find_task_by_pid(pid);//pointer to task
	if(!task){
		res = -ESRCH;
		printk("this pid->%d does not belong to any task error_num %d\n" , pid , res);
		return res;
	}
	if(password != 234123){
		res = -EINVAL;
		printk("wrong password -> %d error_num %d\n" , password,res);
		return res;
	}
	if(task->feature_status == 1){
		res = -EINVAL;
		printk("feature_status is already on error_num %d\n" , res);
		return res;
	}
	if(size<0){
		res = -EINVAL;
		printk("bad size input size->%d\n" ,size);
		return res;
	}
	task->log_array = kmalloc(sizeof(*(task->log_array))*size,GFP_KERNEL);
	if(!task->log_array){
		res = -ENOMEM;
		return res;
	}
	task->size_log_array = size;
	task->num_of_error = 0;
	task->privilege_level = 2;
	task->feature_status=1;
	
	res = 0;
	return res;
}
