# golang相关知识点

## go的锁实现

## go的WaitGroup实现
`WaitGroup`定义如下:
```
type WaitGroup struct {
	noCopy noCopy

	// 64-bit value: high 32 bits are counter, low 32 bits are waiter count.
	// 64-bit atomic operations require 64-bit alignment, but 32-bit
	// compilers do not ensure it. So we allocate 12 bytes and then use
	// the aligned 8 bytes in them as state, and the other 4 as storage
	// for the sema.
	state1 [3]uint32
}
```
其中`state1`有12个字节, 8个字节为state, 还有4个字节为sema. 考虑到32位机器上实现原子操作需要按8个字节对齐, 所以如果state1的地址是8字节对齐的, 则前8个字节为state, 后4个字节为sema, 否则, 前4个字节为sema, 后8个字节为state. 
其中state的前4个字节为counter, 后四个字节为waiter的数量. 

简单来说, 通过atomic原子操作, Add的时候操作counter, 当counter值为0时, 通过`runtime_Semrelease`释放信号量sema waiter次. 而在Wait的时候, 则使用原子操作将waiter +1, 如果加1成功, 则开始等待信号量sema. 

## go的sync.Pool实现


## go的select实现


## go的goroutine实现


## go的defer的顺序

## go中的原子操作

## go中http io的封装细节以及与goroutine的调度


## go的引用类型有哪些

## go中函数传值

## go的错误恢复机制, runtime.Debug, recovery()

## go中case语句是否支持多值


## go的反射包

## goroutine泄漏

## go中内存泄漏

## go中gc原理

## go中nil处理

## go中比较符

TODO finish all questions

