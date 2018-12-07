#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define BUTTON 16 //gpio 27
#define DEV_NAME "button_dev"
#define DEV_NUM 243

MODULE_LICENSE("GPL");

int button_open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "OPEN button device\n");

	int ret = gpio_request(BUTTON, "BUTTON");
	gpio_direction_input(BUTTON);
	
	return 0;
}

int button_close(struct inode *pinode, struct file *pfile){// <-> open
	printk(KERN_ALERT "RELEASE button device\n");

	return 0;
}

ssize_t button_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	printk("Read button sensor\n");

	int stat;
	int result;	
	stat = gpio_get_value(BUTTON);
	result = copy_to_user(buffer, &stat, sizeof(stat));
	printk("button sensor's value %d\n", stat);

	return 0;
}

struct file_operations fop = {
	.owner = THIS_MODULE,
	.open = button_open,
	.read = button_read,
	.release = button_close,

};

int __init button_init(void){
	printk(KERN_ALERT "INIT button device\n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);

	return 0;
}

void __exit button_exit(void){
	printk(KERN_ALERT "exit button device\n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}


module_init(button_init);
module_exit(button_exit);
