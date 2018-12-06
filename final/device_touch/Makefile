KERNELDIR = /lib/modules/$(shell uname -r)/build 

obj-m := touch_dev.o

PWD := $(shell pwd)

default : 
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean

upload :
	sudo insmod touch_dev.ko
	sudo mknod -m 666 /dev/touch_dev c 240 0

remove :
	sudo rmmod touch_dev
	sudo rm -rf /dev/touch_dev 


