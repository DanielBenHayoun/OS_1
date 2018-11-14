#include <sys/types.h>
#include <stdio.h>
#include <errno.h>

struct forbidden_activity_info{
	int syscall_req_level;
	int proc_level;
	int time;
};

int enable_policy(pid_t pid, int size, int password){
	unsigned int res;
	__asm__ (
	    "int $0x80;"
		: "=a" (res)
		: "0" (243) ,"b" (pid) ,"c" (size) , "d" (password)
		: "memory"
	);
	
	if((res)<0){
		errno = -(res);
		return -1;
	}
	
	return res;
}

int disable_policy(pid_t pid , int password){
	unsigned int res;
	__asm__ (
	    "int $0x80;"
		: "=a" (res)
		: "0" (244) ,"b" (pid) ,"c" (password) 
		: "memory"
	);
	
	if((res)<0){
		errno = -(res);
		return -1;
	}
	
	return res;
}

int set_process_capabilities(pid_t pid,int new_level,int password){
	unsigned int res;
	__asm__ (
	    "int $0x80;"
		: "=a" (res)
		: "0" (245) ,"b" (pid) ,"c" (new_level) , "d" (password)
		: "memory"
	);
	
	if((res)<0){
		errno = -(res);
		return -1;
	}
	return res;
}