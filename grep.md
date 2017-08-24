when using grep, how to match '-'?
1. Quote AND/OR escape
Code:
 ls | grep "\-a"
(that \ is the escape character)
or
2. Use flag "--" to stop switch parsing
Code:
ls | grep -- -a
