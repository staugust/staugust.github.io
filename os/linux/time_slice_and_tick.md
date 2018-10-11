# time slice & clock tick

A time slice has nothing to do with clock tick. 
Whenever a task calls system call `sleep`, then the os would re-schedule tasks. Or 


# How to implement timer with higher precision than clock tick? 

It's common that the os 


# 时间片与时钟中断

Linux进程调度时机主要有:
+ 进程状态转换的时刻: 进程中止, 进程睡眠
  进程需要调用`sleep`或`exit`等函数进行状态转换, 这些函数会主动调用调度程序进行进程调度.
+ 当前进程的时间片用完时
  由于进程的时间片是由时钟中断来更新的, 因此这种情况和 4 是一样的.
+ 设备驱动程序
  当设备驱动程序执行长而重复的任务时, 直接调用调度程序. 在每次反复循环中, 驱动程序都检查 need\_resched的值, 如果必要, 则调用调度程序`schedule()`主动放弃CPU
+ 进程从中断, 异常及系统调用返回到用户态时
  不管是从中断, 异常还是系统调用返回, 最终都调用`ret_from_sys_call()`, 由这个函数进行调度标志的检测, 如果必要, 则调用调度程序. 从系统调用返回时调用调度程序主要是从效率的角度来考虑的, 系统调用时处于内核态, 在调用结束返回用户态之前, 调用调度程序, 避免了单独调用调度程序时, 内核态,用户态的切换.

  从上述角度来分析, 可知, 时间片是大于等于时钟中断的. 



