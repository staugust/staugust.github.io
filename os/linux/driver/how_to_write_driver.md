# TODO how to write linux driver and expose API to userspace process


       将设备可映射内存空间文件(resource0, resource1, ... resource5), 即将/sys/devices/.../resource2文件通过mmap映射到进程虚拟地址空间进行读写. 将设备的交互通过/dev文件的方式暴露出来供用户使用.

##   实现原理及代码说明
将设备的交互通过/dev文件的方式暴露出来供用户使用需要以下几个步骤:

 驱动初始化时创建相应的设备, 为设备分配主,次设备号
 为新创建的设备设置相应的系统调用回调函数
 卸载驱动时, 删除相应的设备

### 创建设备, 设置相应的系统调用回调函数
驱动初始化时, 调用一下函数, 创建相应的设备.

```cpp
static int test_mmap_init(struct pci_dev *dev, struct test_device *test_dev) {
    struct test_mmap * emap = &test_dev->testMmap;

    const struct file_operations *fops;
    char name[32] = {};

    sprintf(name, "test_regs_chip%d", test_dev->chip_index);
    if (alloc_chrdev_region(&emap->cdevno, 0, 1, name) < 0) {  // 首先系统申请未使用的设备主,次设备号, 此处alloc_chrdev_region为申请一个字符设备
        goto error;
    }

    /* register file operation */
    fops = &test_mmap_fops;
    cdev_init(&emap->cdev, fops); // 为设备绑定相应的系统调用回调函数

    if (cdev_add(&emap->cdev, emap->cdevno, 1) < 0) {
        goto error;
    }

    if (device_create(test_pci_class, NULL, emap->cdevno, NULL, name) ==  NULL) {  // 创建设备文件节点, 即 /dev/test_regs_chip0 /dev/test_regs_chip1 等等
        pr_err("create device %s error", name);
        goto error;
    }
    emap->created = 1;
    emap->parent = test_dev;
    atomic_set(&emap->token, 1);
    return 0;

    error:
    test_clean_mmap(emap);
    return -1;

}
```

### 系统调用回调函数分析
上节中有一个结构体struct file_opoerations, 即为设备文件操作的回调, 当用户对创建出来的设备文件(本例即为/dev/test_regs/chip*)操作时, 内核通过设备文件注册的结构体, 查找到相应的file_operations实例, 调用相应的函数.

```cpp
static int test_mmap_open(struct inode *inode, struct file *file){
    struct test_mmap *testMmap;
    printk(KERN_ALERT"device mmap open\n");

    if (MINOR(inode->i_rdev) != DEVICE_MINOR_NUM) {
        printk(KERN_ERR "Minor number %d is not equal to %d",
               MINOR(inode->i_rdev), DEVICE_MINOR_NUM);
        return -EINVAL;
    }
    testMmap = container_of(inode->i_cdev, struct test_mmap, cdev);
    /* ignore this, tflex open this file twice
    if (!atomic_dec_and_test(&testMmap->token)) {
        atomic_inc(&testMmap->token);
        return -EBUSY; // already open
    }
    */

    file->private_data = testMmap;
    return 0;
}

static int test_mmap_mmap(struct file *filp, struct vm_area_struct *vma) {
    //TODO aug need to write mmap function
    int rc;
    struct test_mmap *emap = filp->private_data;
    struct test_device * test_dev = container_of(emap, struct test_device, testMmap); // 获取当前设备文件对应的test_device
    // unsigned long page = virt_to_phys(test_dev->bar[EPU_REG_BAR]);
    unsigned long off = vma->vm_pgoff << PAGE_SHIFT; //计算内存映射偏移量
    unsigned long page = pci_resource_start(test_dev->pdev, EPU_REG_BAR); // 当前EPU设备的寄存器区域的起始物理地址
    unsigned long physical = page + off; // 映射起始地址(物理地址+偏移量)
    unsigned long vsize = vma->vm_end - vma->vm_start; // 内存映射区域总长度
    unsigned long psize = pci_resource_end(test_dev->pdev, EPU_REG_BAR) - physical + 1; //当前EPU设备寄存器区域的end物理地址, 减去映射起始地址, 得到当前设备可映射内存大小
    printk(KERN_INFO "off is %ld, page is %ld\n", off, page);
    if (vsize > psize ){ // 如果可映射内存大小小于用户申请的映射大小, 说明mmap的参数不对, 请求映射的区域大于可映射区域
    printk(KERN_INFO "request for %ld while acturally has %ld\n", vsize, psize);
        return -EINVAL;
    }
    rc=io_remap_pfn_range(vma,vma->vm_start,physical >> PAGE_SHIFT,vsize,vma->vm_page_prot); // 通过io_remap_pfn_range 将EPU设备寄存器区域的内存页映射到进程虚拟地址空间, 返回此地址, 进程即可通过此地址直接访问EPU寄存器
    if(rc){
        printk(KERN_INFO "io_remap_pfn_range returns %d\n", rc);
        return -EAGAIN;
    }
    return 0;
}

static int test_mmap_release(struct inode *inode, struct file * filp) {
    //TODO aug done
    struct test_mmap *testMmap = filp->private_data;

    atomic_inc(&testMmap->token);
    filp->private_data = NULL;
    return 0;
}

static const struct file_operations test_mmap_fops = {
        .owner = THIS_MODULE,
        .open = test_mmap_open, // 当用户程序调用系统调用open打开设备文件时, 内核调用此函数
        .mmap = test_mmap_mmap, // 当用户程序调用系统调用mmap将设备文件映射到进程虚拟地址空间时, 内核调用此函数, 将相应设备内存映射到进程虚拟地址空间
        .release = test_mmap_release, // 当用户程序释放资源
};

```



