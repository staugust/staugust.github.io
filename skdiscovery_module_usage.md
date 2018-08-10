# Ray使用说明
Ray是一个灵活的，高性能的分布式执行框架。使用Ray之前，需要先了解以下两点：
- Ray异步执行任务实现并行的机制
- Ray使用对象IDs代表远程不可变对象(`Immutable remote objects`)的原理

## 概览

Ray是一个基于python的分布式引擎。同样的代码既可以在单一节点上执行以充分利用多进程优势，也能在集群中运行以执行海量运算。

Ray的运行过程中，有以下进程参与：
+ 多个worker进程执行任务，并将结果保存到对象仓库中。每一个worker都是一个独立的进程。
+ 每个节点上都有一个对象仓库(`object store`)，对象仓库将不可变对象存储在共享内存中，运行在同一节点上的worker进程能以最小的复制、反序列化代价来高效地共享对象。
+ 每个节点上都有一个本地调度器(`local scheduler`)，用于将任务分发到本节点的worker进程。
+ 一个全局调度器(`global scheduler`)从本地调度器接收任务，并将任务分配给其他节点上的本地调度器。
+ 一个驱动进程(`driver`)是一个用户控制的python进程。举个例子，如果用户运行一个python脚本，或者使用Python shell，那么驱动程序就是运行用户脚本的python进程，或者shell进程。
+ Redis服务端(`redis server`)维持当前系统的大部分状态，比如说，其保存每个对象存储在哪个节点的对象仓库。

## 启动Ray(单机模式)
首先启动python shell，在python shell中执行以下命令即可启动ray：
```
import ray
ray.init()
```

## 启动Ray(集群模式)
SkyDiscovery环境尚未准备好，待完善。

## 远程不可变对象
在Ray中，我们可以创建对象，并使用对象来计算，称这些对象为远程对象，使用对象IDs来指代它们。远程对象存储在对象仓库中，在集群中，每个节点上有且只有一个对象仓库。在集群模式下，我们实际上可能并不清楚每个对象存储在哪个节点上。

对象ID实质上是一个唯一的ID，用于指代一个远程对象。如果你对Futures比较熟悉，对象ID在概念上与其相似。

我们认为远程对象都是不可变的，也就是说，当对象被创建之后，它们的值不可再被更改。这个机制允许将远程对象复制到多节点的对象仓库而无需同步操作(不可变对象复制到多个节点即可，如果是可变对象，则复制到其他节点之后，当对象被更新时，需要将更新同步到其他节点的副本上)。

### 对象存取(Put and Get)
ray提供`ray.put`和`ray.get`方法来存取python对象，如下面例子所示：
```
x = "example"
ray.put(x) # ObjectID(b49a32d72057bdcfc4dda35584b3d838aad89f5d)
```
`ray.put(x)`将被worker进程或者驱动进程执行，将一个python的对象复制到其本地对象仓库，一旦对象被存储到对象仓库后，其值将不可被更改。
另外，`ray.put(x)`返回一个对象ID，可用此对象ID来读取刚刚创建的远程对象。如果我们使用代码`x_id = ray.put(x)`将对象ID保存到一个变量中，稍后我们就可将`x_id`传递给远程方法，远程方法将在`x_id`指向的对象中做出相应的操作。

`ray.get(x_id)`从对象仓库中读取`x_id`指代的对象，并创建一个python对象保存下来。如果远程对象并不在当前节点的对象仓库中，则首先将远程对象从保存此远程对象的对象仓库中复制到本地对象仓库。
```
x_id = ray.put("example")
ray.get(x_id) # "example"
```
如果对应`x_id`的远程对象尚未创建，则`ray.get(x_id)`会一直等到对象被创建。

## Ray的异步运算

Ray通过使用装饰器将python方法装饰为远程方法(`remote function`)以支持异步执行任意的python方法。
比如说，一个简单的python方法如下：
```
def add1(a, b):
    return a + b
```
远程方法则如下：
```
@ray.remote
def add2(a, b):
    return a + b
```

### 远程方法(remote function)
调用 `add1(1,2)`时返回`3`并导致python解释器阻塞直到计算结束，调用`add2.remote(1,2)`则立即返回一个远程对象ID，并创建一个任务(`task`)，ray集群调度并异步执行此任务。当任务执行完毕，将返回值存储到对象仓库中。
```
x_id = add2.remote(1, 2)
ray.get(x_id)  # 3
```

下面是一个简单的展示如何异步并行执行计算任务的例子：
```
import time

def f1():
    time.sleep(1)

@ray.remote
def f2():
    time.sleep(1)

# 此行执行需要10秒。
[f1() for _ in range(10)]

# 此行执行需要1秒（假设当前系统有至少10个CPU）
ray.get([f2.remote() for _ in range(10)])
```

提交任务(`submit task`)和执行任务(`execute task`)有明显的区别，当远程方法(`remote function`)被调用时，首先将此任务提交到本地调度器，并立刻返回指向远程方法返回对象的ID，直到系统实际上将任务分发到worker进程之后，任务才被执行。
提交任务时，参数可以是python对象(值)，也可以是对象ID，下面例子上的几行有同样的结果。
```
add2.remote(1, 2)
add2.remote(1, ray.put(2))
add2.remote(ray.put(1), ray.put(2))
```
另外，远程方法可以返回多个对象ID。
```
@ray.remote(num_return_vals=3)
def return_multiple():
    return 1, 2, 3

a_id, b_id, c_id = return_multiple.remote()
```

### 任务间的依赖

可以将远程方法返回的对象ID传递给别的远程方法，以下例子提交了三个任务，每个任务都依赖前一个任务的返回值。
```
@ray.remote
def f(x):
    return x + 1

x = f.remote(0)
y = f.remote(x)
z = f.remote(y)
ray.get(z) # 3
```
直到第一个任务结束，第二个任务才会开始，同理，直到第二个任务执行结束，则开始执行第三个任务。显然，本例中的三个任务无法并行执行。

这种构建任务的方式简化了表达多任务之间的依赖，如下例所示：
```
import numpy as np

@ray.remote
def generate_data():
    return np.random.normal(size=1000)

@ray.remote
def aggregate_data(x, y):
    return x + y

# Generate some random data. This launches 100 tasks that will be scheduled on
# various nodes. The resulting data will be distributed around the cluster.
data = [generate_data.remote() for _ in range(100)]

# Perform a tree reduce.
while len(data) > 1:
    data.append(aggregate_data.remote(data.pop(0), data.pop(0)))

# Fetch the result.
ray.get(data)
```

### 在远程方法中调用远程方法

之前的例子仅展现了通过驱动进程调用远程方法，在worker进程中也可以调用远程方法，比方说：
```
@ray.remote
def sub_experiment(i, j):
    # Run the jth sub-experiment for the ith experiment.
    return i + j

@ray.remote
def run_experiment(i):
    sub_results = []
    # Launch tasks to perform 10 sub-experiments in parallel.
    for j in range(10):
        sub_results.append(sub_experiment.remote(i, j))
    # Return the sum of the results of the sub-experiments.
    return sum(ray.get(sub_results))

results = [run_experiment.remote(i) for i in range(5)]
ray.get(results) # [45, 55, 65, 75, 85]
```
当远程方法`run_experiment`在worker进程上执行时，它将调用`sub_experiment`数次。本例说明了如何并行的计算以缩短计算时间。


# Caffe使用说明

Caffe是一个清晰高效的深度学习框架，其作者是毕业于UC Berkeley的贾扬清。Caffe是纯粹的c++/CUDA架构，支持命令行，Python及Matlab接口，可以在CPU/GPU无缝切换，使用如下代码：
```
Caffe::set_mode(Caffe::GPU)
```
本文旨在说明如何在SkyDiscovery环境中使用Caffe，Caffe的详细API文档请参考其官网：
```
http://caffe.berkeleyvision.org/
```
## Caffe with Python
Caffe封装好的Python接口即为Python库，可通过以下代码导入Caffe库：
```
import caffe
```

下面是一个简单的例子，说明如何构建一个Caffe的神经网络：
```
from __future__ import print_function
from caffe import layers as L, params as P, to_proto
from caffe.proto import caffe_pb2

# helper function for common structures

def conv_relu(bottom, ks, nout, stride=1, pad=0, group=1):
    conv = L.Convolution(bottom, kernel_size=ks, stride=stride,
                                num_output=nout, pad=pad, group=group)
    return conv, L.ReLU(conv, in_place=True)

def fc_relu(bottom, nout):
    fc = L.InnerProduct(bottom, num_output=nout)
    return fc, L.ReLU(fc, in_place=True)

def max_pool(bottom, ks, stride=1):
    return L.Pooling(bottom, pool=P.Pooling.MAX, kernel_size=ks, stride=stride)

def caffenet(lmdb, batch_size=256, include_acc=False):
    data, label = L.Data(source=lmdb, backend=P.Data.LMDB, batch_size=batch_size, ntop=2,
        transform_param=dict(crop_size=227, mean_value=[104, 117, 123], mirror=True))

    # the net itself
    conv1, relu1 = conv_relu(data, 11, 96, stride=4)
    pool1 = max_pool(relu1, 3, stride=2)
    norm1 = L.LRN(pool1, local_size=5, alpha=1e-4, beta=0.75)
    conv2, relu2 = conv_relu(norm1, 5, 256, pad=2, group=2)
    pool2 = max_pool(relu2, 3, stride=2)
    norm2 = L.LRN(pool2, local_size=5, alpha=1e-4, beta=0.75)
    conv3, relu3 = conv_relu(norm2, 3, 384, pad=1)
    conv4, relu4 = conv_relu(relu3, 3, 384, pad=1, group=2)
    conv5, relu5 = conv_relu(relu4, 3, 256, pad=1, group=2)
    pool5 = max_pool(relu5, 3, stride=2)
    fc6, relu6 = fc_relu(pool5, 4096)
    drop6 = L.Dropout(relu6, in_place=True)
    fc7, relu7 = fc_relu(drop6, 4096)
    drop7 = L.Dropout(relu7, in_place=True)
    fc8 = L.InnerProduct(drop7, num_output=1000)
    loss = L.SoftmaxWithLoss(fc8, label)

    if include_acc:
        acc = L.Accuracy(fc8, label)
        return to_proto(loss, acc)
    else:
        return to_proto(loss)

def make_net():
    with open('train.prototxt', 'w') as f:
        print(caffenet('/path/to/caffe-train-lmdb'), file=f)

    with open('test.prototxt', 'w') as f:
        print(caffenet('/path/to/caffe-val-lmdb', batch_size=50, include_acc=True), file=f)

if __name__ == '__main__':
    make_net()
```

## Caffe C++接口

Caffe也提供了C++接口，相关的头文件(.hpp)位置为`.../SkyDisocvery/include/caffe`，相应的动态库在`.../SkyDiscovery/lib/`下。

# Caffe2使用说明

Caffe是一个新的轻量级、模块化、可伸缩的深度学习框架，致力于提供提供简单直观的方法来实验深度学习。本文旨在说明如何在SkyDiscovery环境下使用Caffe2，Caffe2的详细API请参考其官方网站：
```
https://caffe2.ai
```

## Caffe2 Python接口
Caffe2封装好的Python接口即为Python库，可通过以下代码导入Caffe2库：
```
import caffe2
```

下面是一个简单的例子，说明如何使用Caffe2来处理数据。
```
from caffe2.python import workspace, model_helper
import numpy as np
# Create random tensor of three dimensions
x = np.random.rand(4, 3, 2)
print(x)
print(x.shape)

workspace.FeedBlob("my_x", x)

x2 = workspace.FetchBlob("my_x")
print(x2)
```

## Caffe2 C++接口

Caffe2也提供了C++接口，相关的头文件(.hpp)位置为`.../SkyDisocvery/include/caffe2`，相应的动态库在`.../SkyDiscovery/lib/`下。