# Slice params in func

Given code below:
```go
package main

import "fmt"

func passSlice(s []int, k *int) {
	if *k >9 {
		return
	}
	tmp := *k
	if tmp >= 5 {
		s[tmp - 5] = tmp
	} else {
		s = append(s, *k)
	}
	fmt.Println("Before sub call ", tmp, s)
	*k += 1
	passSlice(s, k)
	fmt.Println("After sub call ", tmp, s)
}

func main() {
	s := make([]int, 0)
	stk := 0
	fmt.Println(s)
	passSlice(s, &stk)
}

```
Can you imagine the output of this code snippet? 


```bash
[]
Before sub call  0 [0]
Before sub call  1 [0 1]
Before sub call  2 [0 1 2]
Before sub call  3 [0 1 2 3]
Before sub call  4 [0 1 2 3 4]
Before sub call  5 [5 1 2 3 4]
Before sub call  6 [5 6 2 3 4]
Before sub call  7 [5 6 7 3 4]
Before sub call  8 [5 6 7 8 4]
Before sub call  9 [5 6 7 8 9]
After sub call  9 [5 6 7 8 9]
After sub call  8 [5 6 7 8 9]
After sub call  7 [5 6 7 8 9]
After sub call  6 [5 6 7 8 9]
After sub call  5 [5 6 7 8 9]
After sub call  4 [5 6 7 8 9]
After sub call  3 [0 1 2 3]
After sub call  2 [0 1 2]
After sub call  1 [0 1]
After sub call  0 [0]
[]
```
Why? 

The reference to the underlying array is a value, and in Go, everything is passed by value (even pointers/references). So your function that receives a slice is receiving a copy of the slice header. The slice header contains important information like starting address and size. When you append to the slice in your other function, the copy of the slice header gets modified, but the original calling function doesn't see that copy, it still has its own. That's why functions like append return the new value, which is the modified slice header.;

And why after sub call, it's not all `[5 6 7 8 9]` ? Because the slice's data segment was re-alloced. 


```go
package main

import "fmt"

func passSlice(s []int, k *int) {
	if *k >9 {
		return
	}
	tmp := *k
	if tmp >= 5 {
		s[tmp - 5] = tmp
	} else {
		s = append(s, *k)
	}
	fmt.Println("Before sub call ", tmp, cap(s) , s)
	*k += 1
	passSlice(s, k)
	fmt.Println("After sub call ", tmp, cap(s), s)
}

func main() {
	s := make([]int, 0)
	stk := 0
	fmt.Println(s, cap(s))
	passSlice(s, &stk)
	fmt.Println(s, cap(s))
}

```
Output of code above:

```
[] 0
Before sub call  0 1 [0]
Before sub call  1 2 [0 1]
Before sub call  2 4 [0 1 2]
Before sub call  3 4 [0 1 2 3]
Before sub call  4 8 [0 1 2 3 4]
Before sub call  5 8 [5 1 2 3 4]
Before sub call  6 8 [5 6 2 3 4]
Before sub call  7 8 [5 6 7 3 4]
Before sub call  8 8 [5 6 7 8 4]
Before sub call  9 8 [5 6 7 8 9]
After sub call  9 8 [5 6 7 8 9]
After sub call  8 8 [5 6 7 8 9]
After sub call  7 8 [5 6 7 8 9]
After sub call  6 8 [5 6 7 8 9]
After sub call  5 8 [5 6 7 8 9]
After sub call  4 8 [5 6 7 8 9]
After sub call  3 4 [0 1 2 3]
After sub call  2 4 [0 1 2]
After sub call  1 2 [0 1]
After sub call  0 1 [0]
[] 0
```

See [slice pass-by-reference](https://www.reddit.com/r/golang/comments/283vpk/help_with_slices_and_passbyreference/).
