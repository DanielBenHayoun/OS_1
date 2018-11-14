#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>

int sys_enable_policy(pid_t pid, int size, int password){
	int res;
	
	//parameters tests
	if(pid<0){
		res = -ESRCH;
		return res;
	}
	task_t* task = find_task_by_pid(pid);//pointer to task
	if(!task){
		res = -ESRCH;
		return res;
	}
	if(password != 234123){
		res = -EINVAL;
		return res;
	}
	if(task->feature_status == 1){
		res = -EINVAL;
		return res;
	}
	if(size<0){
		res = -EINVAL;
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

int sys_disable_policy(pid_t pid , int password){
	int res;
	
	if(pid<0){
		res = -ESRCH;
		return res;
	}
	task_t* task = find_task_by_pid(pid);//pointer to task
	if(!task){
		res = -ESRCH;
		return res;
	}
	if(task->feature_status == 0){
		res = -EINVAL;
		return res;
	}
		if(password != 234123){
		res = -EINVAL;
		return res;
	}
	kfree(task->log_array);
	task->size_log_array =0;
	task->num_of_error = 0;
	task->privilege_level = 2;
	task->feature_status=0;
	
	res = 0;
	return res;
	
}

int sys_get_process_log(pid_t pid,int size,struct forbidden_activity_info* user_mem){
	int res;
	
	if(pid<0){
		res = -ESRCH;
		return res;
	}
	task_t* task = find_task_by_pid(pid);//pointer to task
	if(!task){
		res = -ESRCH;
		return res;
	}
	if(size > task->num_of_error || size < 0 || task->feature_status == 0) {
		res=-EINVAL;
		return res;
	}
	
	res = 0;
	return res;

}