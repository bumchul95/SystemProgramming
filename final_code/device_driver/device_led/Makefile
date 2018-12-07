KERNELDIR = /lib/modules/$(shell uname -r)/build 

obj-m := led_dev.o

PWD := $(shell pwd)

default : 
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean

upload :
	sudo insmod led_dev.ko
	sudo mknod -m 666 /dev/led_dev c 233 0

remove :
	sudo rmmod led_dev
	sudo rm -rf /dev/led_dev 


