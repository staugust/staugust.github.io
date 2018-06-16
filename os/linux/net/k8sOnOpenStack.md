# 解决k8s在openstack上pods之间无法通信问题

通过tcpdump抓包之后，可以看到包在送到对应的host上，传给qbr之后，没有传给相应的虚拟机的tap网卡. 
然后通过iptables，检查qbr相关的包信息，发现问题，iptables drop相应的ip in ip协议的IP包。
解决方案: 

在openstack dashboard上，安全组添加安全规则，允许ip in ip 协议即可。
