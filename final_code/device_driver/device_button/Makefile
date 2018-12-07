KERNELDIR = /lib/modules/$(shell uname -r)/build 

obj-m := button_dev.o

PWD := $(shell pwd)

default : 
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean

upload :
	sudo insmod button_dev.ko
	sudo mknod -m 666 /dev/button_dev c 238 0

remove :
	sudo rmmod button_dev
	sudo rm -rf /dev/button_dev 


