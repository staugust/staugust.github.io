# block
Lines between the braces {} are called a block.
Since whitespace is irrelevant to the Java compiler, there're many brace styles, one can use any style as he likes. 

# Comment
Comments do not show up in the executable program. 
Java has three ways of marking comments. 
1. use **//**
```
System.out.println("Hello world!"); // comment here
```
2. use __/\*__ and __\*/__
```
/* comment here
 */
```
3. use __/\*\*__ and __\*/__
```
/** comment
 * comment 
 */
```
# Data Types
Java is a *strongly typed language*. There're 8 *primitive types* in Java. 

+ long     8 bytes  -9223372036854775808 ~ 9223372036854775807
+ int      4 bytes  -2147483648          ~ 2147483647 (just over 2 billion)
+ short    2 bytes  -32768               ~ 32767
+ byte     1 bytes  -128                 ~ 127
+ float    4 bytes  6-7 significant decimal digits (a sign 1bit, a mantissa 23bits, a radix, an exponent 8bits, refer to IEEE-754 1985) [s eeeeeeee mmmmmmmmmmmmmmmmmmmmmmm]
+ double   8 bytes  15 significant decimal digits (a sign 1bit, a mantissa 52bits, a radix, an exponent 11bits) 
+ char              Unicode characters
+ boolean  true/false

---
+ To encode U+10437 (𐐷) to UTF-16:

Subtract 0x10000 from the code point, leaving 0x0437.
For the high surrogate, shift right by 10 (divide by 0x400), then add 0xD800, resulting in 0x0001 + 0xD800 = 0xD801.
For the low surrogate, take the low 10 bits (remainder of dividing by 0x400), then add 0xDC00, resulting in 0x0037 + 0xDC00 = 0xDC37.
+ To decode U+10437 (𐐷) from UTF-16:

Take the high surrogate (0xD801) and subtract 0xD800, then multiply by 0x400, resulting in 0x0001 * 0x400 = 0x0400.
Take the low surrogate (0xDC37) and subtract 0xDC00, resulting in 0x37.
Add these two results together (0x0437), and finally add 0x10000 to get the final decoded UTF-32 code point, 0x10437.

# Variable Initilization
After a variable is declared, it should be initialized explicitly. For fields in a class, if there's no explicit initialization, **long, int, short, byte, char, float, double** will be initialized as zero, and boolean would be initialized as **false**, at the mean while, objects are initialized as **null**. 

# Operators
Integer division by 0 raises an exception, whereas floating-point division by 0 yields an infinite or NaN result. 
The **double** type uses 64 bits to store a numeric value, but some processors use 80-bit floating-point registers. These registers yield added precision in intermediate steps of a computation. For example, consider the following computation:
```
double w = x * y / z;
```
Many Intel processors compute **x\*y**, leave the result in an 80-bit register, then divide by **z**, and finally truncate the result back to 64 bits. That can yield a more accurate result, and it can avoid exponent overflow. But the result may be **different** from a computation that uses 64 bits throughout. As a result, methods tagged with the **strictfp** keyword must use strict floating-point operations that yield reproducible results. 
For example, you can tag `main` as 
```
public static strictfp void main(String[] args)
```
Then all instructions inside the `main` method will use strict floating-point computations. If you tag a class as **strictfp**, then all of its methods must use strict floating-point computations. 

