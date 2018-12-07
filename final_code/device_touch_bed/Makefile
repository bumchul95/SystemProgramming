KERNELDIR = /lib/modules/$(shell uname -r)/build 

obj-m := bed_touch_dev.o

PWD := $(shell pwd)

default : 
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean

upload :
	sudo insmod bed_touch_dev.ko
	sudo mknod -m 666 /dev/bed_touch_dev c 240 0

remove :
	sudo rmmod bed_touch_dev
	sudo rm -rf /dev/bed_touch_dev 


