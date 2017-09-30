# Numpy tutorial

## The basics
In NumPy dimensions are called axes. The number of axes is rank.
For example, the coordinates of a point in 3D space [1, 2, 1] is an array of rank 1, because it has one axis. That axis has a length of 3. In the example pictured below, the array has rank 2 (it is 2-dimensional). The first dimension (axis) has a length of 2, the second dimension has a length of 3.
```
[[ 1., 0., 0.],
 [ 0., 1., 2.]]
```

## Array Creation
There are several ways to create arrays.

``numpy.array`` creates array with python iterable object.
```
import numpy as np
np.array( [ i for i in range(10)])  # Use python list
np.array( (1,2,3))  # Use python tuple
np.array( set([1,2,3])) # Use python set
np.array([(1.5,2,3), (4,5,6)]) # create two-dimensional array
```

``numpy.zeros`` creates an array full of zeros, while ``numpy.ones`` creates an array full of ones. And ``numpy.empty`` creates an array whose initial content is random and depends on the state of the memory. By default, the dtype of the created array is `float64`.
```
import numpy as np
np.zeros( (3,4))  # create an array with shape (3,4)
np.empty( (3,4))
```
``numpy.arange(start, stop, step)`` will create sequences of numbers.
``numpy.lnspace(start, stop, total_elements)`` will create  sequences of numbers too.
```
import numpy as np
np.arange(10,30,5)  # array([10, 15, 20, 25])
np.linspace(0,2,9)  # array([ 0.  , 0.25, 0.5, ... , 1.75, 2])
```
## Basic Operations
Arithmetic operators on arrays apply elementwise. 
```
>>> A = np.array( [[1,1],
...             [0,1]] )
>>> B = np.array( [[2,0],
...             [3,4]] )
>>> A*B                         # elementwise product
array([[2, 0],
       [0, 4]])
>>> A.dot(B)                    # matrix product
array([[5, 4],
       [3, 4]])
>>> np.dot(A, B)                # another matrix product
array([[5, 4],
       [3, 4]])                 # [ [ A[0,:] * B[:,0], A[0,:] * B[:,1] ],
                                #   [ A[1,:] * B[:,0], A[1,:] * B[:,1] ]
```




















