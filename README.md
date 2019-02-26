OS_1

# Introduction
The goal in this assignment will be to add new system calls to the kernel’s interface and to
change some existing system calls. Furthermore, in this exercise, we will use VMware to simulate a virtual machine on
which we will compile and run our "modified" Linux. 
## General Description
We want  to prohibit certain processes from calling specific system calls. To do so, we will
add new features to the Linux kernel wherein every process is associated with a specific
privilege level. Then, we will modify some existing system calls, that we have learned about,
such that only a process with an appropriate privilege level will be able to invoke them. Finally,
we will create a logging service that records forbidden activities of processes in the OS.
### The policy is defined as follows:

* Turning On The Policy Feature: By default, all processes will not be affected by this
feature. we will define a system call which gets the PID of a process and turns on the
feature for this process. If the feature is turned off for a process, then the process
executes as normal and is not affected by anything in this homework exercise,
regardless of its privilege level.

● Privilege Level: Each process should have a privilege level in the range of [0,2].
Processes by default start with privilege level 2 when the policy feature is set on for
them.

**Note: this definition of privilege level is not related to CPL.**

● Setting the Privilege Level: Every process may set the privilege level of any other
process (including itself) through special system calls. These system calls require an
administrator’s password which will be sent as a parameter.

● Effects of the Privilege Level:
 For each of the system calls, if the calling process has a privilege level which is
strictly lower than the threshold of that system call and the policy feature was set
on for this process, then the call should fail and return -EINVAL. We define such
behavior as a forbidden activity.

**Clarification: A system call with threshold x can only be executed by a process
which has a privilege level greater than or equal to x.**
