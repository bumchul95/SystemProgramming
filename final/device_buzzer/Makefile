KERNELDIR = /lib/modules/$(shell uname -r)/build 

obj-m := buzzer_dev.o

PWD := $(shell pwd)

default : 
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean

upload :
	sudo insmod buzzer_dev.ko
	sudo mknod -m 666 /dev/buzzer_dev c 241 0

remove :
	sudo rmmod buzzer_dev
	sudo rm -rf /dev/buzzer_dev 


