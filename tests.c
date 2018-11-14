#include <sys/types.h>
#include <unistd.h>
#include <sched.h>

#include "hw1_syscalls.h"





	
int main() {
  enable_policy(getpid(),-24,234123);// FAIL
  enable_policy(getpid(),1,2); // FAIL
  enable_policy(-1,1,234123); // FAIL
  enable_policy(getpid()*3,1,234123); // FAIL
  enable_policy(getpid(),1,234123); // FAIL
  
  enable_policy(getpid(),10,234123);  
  
  return 0;
}
