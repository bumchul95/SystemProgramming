KERNELDIR = /lib/modules/$(shell uname -r)/build 

obj-m := pil_touch_dev.o

PWD := $(shell pwd)

default : 
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean

upload :
	sudo insmod pil_touch_dev.ko
	sudo mknod -m 666 /dev/pil_touch_dev c 242 0

remove :
	sudo rmmod pil_touch_dev
	sudo rm -rf /dev/pil_touch_dev 


