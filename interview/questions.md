# From MayiJinfu

1. 有两个文件A, B, 每个文件包含50亿条URL, URL最长为64 byte, 如何判断两文件中是否有URL重复, 如何获取重复的URL. 限制条件: 内存只有4G.
提示: 使用布隆过滤器(bloom filter)
