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
