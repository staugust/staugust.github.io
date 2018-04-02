# jline ConsoleReader hang when using Intellij 
Example code: 
```
package cn.augusto

import jline.console.ConsoleReader
import jline._
/**
  * @Author: Augusto
  * @Description:
  * @Date: Created in 14:08 2018/4/2
  *
  */
object TestConsole{
  def main(args: Array[String]): Unit = {
    val reader = new ConsoleReader()
    var line = ""
    while( (line = reader.readLine("-->")) != null){
      println(line)
    }

  }
}
```
Add jvm options below to avoid this.  
```
-Djline.WindowsTerminal.directConsole=false -Djline.terminal=jline.UnsupportedTerminal 
```
