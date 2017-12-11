# Linux FileSystem

`fdisk` is used to make partitions. It's recommended to make disk partitions at first. 

Then use `pvcreate` to create phisical volume. It's not necessary to create disk partitions before create phisical volume, but it does make sense. If phisical volume is created with raw disk, some OS may run something wrong.

Then create logical group to manage phisical volumes, with command `lvcreate`. 

After that, you can create logical volumes from the logical group with command `lvcreate`. You can create several logical volumes from one logical group. I'm not sure whether a logical volume can use two logical groups. 

Use `mkfs.*` to format logical volumes. 

Finally, use `mount` to mount new created logical volume to a directory. 

Some commands may help to detect file system status:

```
fdisk -l
vgs
vgscan
lvs
lvscan
pvs
pvscan
mount

df 
du 
find

```


