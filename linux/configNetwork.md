# How to configure a network interface to use static addr

modify file `/etc/sysconfig/network-scripts/ifcfg-enp0s3`. 

```
TYPE="Ethernet"
BOOTPROTO="static"
DEFROUTE="yes"
PEERDNS="yes"
PEERROUTES="yes"
IPV4_FAILURE_FATAL="no"
IPV6INIT="yes"
IPV6_AUTOCONF="yes"
IPV6_DEFROUTE="yes"
IPV6_PEERDNS="yes"
IPV6_PEERROUTES="yes"
IPV6_FAILURE_FATAL="no"
NAME="enp0s3"
UUID="43e1845b-436b-4664-a03c-42518b6c1929"
DEVICE="enp0s3"
ONBOOT="yes"

IPADDR=192.168.50.63
NETMASK=255.255.255.0
GATEWAY=192.168.50.1
DNS1=192.168.50.98
DNS2=192.168.20.17
```
