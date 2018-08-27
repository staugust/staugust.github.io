# What would others threads do if main thread completes its operations?
When a java program started, two threads are started. The first code snippet would output `2`. 


In java, main threads 


# Related code
## First code snippet 
```
import java.lang.Thread;
public class Test {
  public static void main(String[] args){
    System.out.println(Thread.activeCount());
  }
}
```
