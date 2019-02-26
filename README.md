OS_1
This excersice is about system- calls.
We added a few syscalls for the linux-2.4.18-14 kernel.
# Introduction
Your goal in this assignment will be to add new system calls to the kernel’s interface and to
change some existing system calls. While doing so you will gain extra knowledge in compiling
the kernel. Furthermore, in this exercise, we will use VMware to simulate a virtual machine on
which we will compile and run our "modified" Linux. You will submit only changed source files of
the Linux kernel.
##### General Description
We want you to prohibit certain processes from calling specific system calls. To do so, you will
add new features to the Linux kernel wherein every process is associated with a specific
privilege level. Then, you will modify some existing system calls, that you have learned about,
such that only a process with an appropriate privilege level will be able to invoke them. Finally,
you will create a logging service that records forbidden activities of processes in the OS.
###### The policy is defined as follows:
● Turning On The Policy Feature: By default, all processes will not be affected by this
feature. You will define a system call which gets the PID of a process and turns on the
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
o Below is a list of some system calls that you have seen in class. For each of
these, we define a minimum privilege level requirement.
o For each of these system calls, if the calling process has a privilege level which is
strictly lower than the threshold of that system call and the policy feature was set
on for this process, then the call should fail and return -EINVAL. We define such
behavior as a forbidden activity.
**Clarification: A system call with threshold x can only be executed by a process**
which has a privilege level greater than or equal to x.
o You should not enforce the policy in any other system call.
● Recording Forbidden Activities: You must define a separate log for each process. If a
process attempts to perform a forbidden activity, then this activity should be recorded in
the log of that process. Specific details on the implementation of the log are discussed
below
