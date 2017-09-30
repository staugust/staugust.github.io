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

``numpy.zeros`` creates an array full of zeros.
``numpy.empty`` creates an array whose initial content is random and depends on the state of the memory. By default, the dtype of the created array is `float64`.
```
import numpy as np
np.zeros( (3,4))  # create an array with shape (3,4)
np.empty( (3,4))
```

