KERNELDIR = /lib/modules/$(shell uname -r)/build 

obj-m := sound_dev.o

PWD := $(shell pwd)

default : 
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean

upload :
	sudo insmod sound_dev.ko
	sudo mknod -m 666 /dev/sound_dev c 246 0

remove :
	sudo rmmod sound_dev
	sudo rm -rf /dev/sound_dev 


