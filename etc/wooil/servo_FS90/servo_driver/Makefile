KERNELDIR = /lib/modules/$(shell uname -r)/build

obj-m := servo_driver.o

PWD := $(shell pwd)

defualt :
	make -C $(KERNELDIR) M=$(PWD) modules

clean :
	make -C $(KERNELDIR) M=$(PWD) clean
