# netfilter

五个netfilter挂载点

+ `NF_INET_PRE_ROUTING`
位于`ip_rcv/ip6_rcv`中, 这是所有入站数据包遇到的第一个挂载点, 它处于路由选择子系统查找之前. 
+ `NF_INET_LOCAL_IN`
位于`ip_local_deliver/ip6_input`中, 对于所有发送给当前主机的入站数据包, 经过挂载点`NF_INET_PRE_ROUTING`并执行路由选择子系统查找之后, 都将到达这个挂载点. 

+ `NF_INET_FORWARD`
位于`ip_forward/ip6_forward`中, 对于所有要转发的数据包, 经过挂载点`NF_INET_PRE_ROUTING`并执行路由选择子系统查找后, 都将到达这个挂载点. 

+ `NF_INET_POST_ROUTING`
位于`ip_output/ip6_finish_output2`中, 所有要转发的数据包都在经过挂载点`NF_INET_FORWARD`后, 到达此挂载点. 另外, 当前主机生成的数据包经过挂载点`NF_INET_LOCAL_OUT`后将到达此挂载点. 

+ `NF_INET_LOCAL_OUT`
位于`__ip_local_out/__ip6_local_out`中. 当前主机生成的所有出站数据包都在经过这个挂载点后, 到达挂载点`NF_INET_POST_ROUTING`.

## Netfilter钩子回调函数的返回值必须为下述值之一:
+ `NF_DROP` (0)  默默丢弃数据包
+ `NF_ACCEPT` (1) 数据包像往常那样继续在内核网络栈中传输. 
+ `NF_STOLEN` (2) 数据包不继续传输, 由钩子方法进行处理
+ `NF_QUEUE`  (3) 将数据包排序, 供用户空间使用
+ `NF_REPEAT` (4) 再次调用钩子函数. 
