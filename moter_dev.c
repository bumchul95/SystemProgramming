#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define MOTER 18 //gpio 1
#define DEV_NAME "moter_dev"
#define DEV_NUM 240

MODULE_LICENSE("GPL");

int moter_open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "OPEN moter device\n");
	
	gpio_request(MOTER, "MOTER");
	gpio_direction_output(MOTER, 1);
	return 0;
}

int moter_close(struct inode *pinode, struct file *pfile){// <-> open
	printk(KERN_ALERT "RELEASE moter device\n");
	
	return 0;
}

ssize_t moter_write(struct file *pfile, const char *buffer, size_t length, loff_t *offset){
	printk("Write moter sensor\n");
        int i;
	
	/*
	for(i=0;i<300;i++){ // 5
	gpio_set_value(MOTER, 1);
	mdelay(3);
	gpio_set_value(MOTER, 0);
	mdelay(3);
	}
	
	
	mdelay(900);
	
	for(i=0;i<1500;i++){ // 24
	gpio_set_value(MOTER, 1);
	mdelay(0.1);
	gpio_set_value(MOTER, 0);
	mdelay(0.1);
	}
	
	mdelay(900);
	*/
	for(i=0;i<500;i++){ // 15
	gpio_set_value(MOTER, 1);
	mdelay(0.1);
	gpio_set_value(MOTER, 0);
	mdelay(0.1);
	}
	
	return length;
}

struct file_operations fop = {
	.owner = THIS_MODULE,
	.open = moter_open,
	.write = moter_write,
	.release = moter_close,

};

int __init moter_init(void){
	printk(KERN_ALERT "INIT moter device\n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);
	
	return 0;
}
void __exit moter_exit(void){
	printk(KERN_ALERT "exit moter device\n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}


module_init(moter_init);
module_exit(moter_exit);
