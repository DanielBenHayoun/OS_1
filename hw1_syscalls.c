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

int sys_set_process_capabilities(pid_t pid,int new_level,int password){
	int res;
	if(new_level != 0 && new_level != 1 && new_level != 2){
		res = -EINVAL;
		printk("the new level->%d is incorrect" , new_level);
		return res;
	}
	if(password != 234123){
		res = -EINVAL;
		printk("wrong password -> %d error_num %d\n" , password,res);
		return res;
	}
	if(task->feature_status == 0){
		res = -EINVAL;
		printk("feature_status is off error_num %d\n" , res);
	if(size > task->num_of_error || size < 0 || task->feature_status == 0) {
		res=-EINVAL;
		return res;
	}
    
 int sys_get_process_log(pid_t pid,int size ,struct forbidden_activity_info* user_mem){
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
	copy_to_user(user_mem, task->log_array, size);
	forbidden_activity_info* new_log_array = kmalloc(sizeof(*(task->log_array))*(task->size_log_array),GFP_KERNEL);
	int j=0;
	for(int i=size; i<task->size_log_array;i++){
	new_log_array[j]=task->log_array[i];
	j++;
	}
	kfree(task->log_array);
	task->log_array=new_log_array;
	res = 0;
	return res;

}