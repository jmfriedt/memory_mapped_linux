Tested on Zynq SOC ARM core, but crashes on amd64 Intel CPU.

For testing, cross-compile the kernel module (``make``) and the userspace 
application (``arm-linux-gcc -o mymmap_userspace mymmap_userspace.c`` assuming
the Buildroot compiler direction ``output/host/usr/bin`` is in the PATH), and 
on the Redpitaya:
```sh
mknod /dev/mydev c 91 0
insmod mymmap.ko
./mymmap_userspace
```
