KERNELDIR = /lib/modules/$(shell uname -r)/build 

obj-m := motor_dev.o

PWD := $(shell pwd)

default : 
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean

upload :
	sudo insmod motor_dev.ko
	sudo mknod -m 666 /dev/motor_dev c 243 0

remove :
	sudo rmmod motor_dev
	sudo rm -rf /dev/motor_dev 


