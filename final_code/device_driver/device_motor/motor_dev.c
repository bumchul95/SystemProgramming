#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define MOTOR 26 //gpio 25
#define DEV_NAME "motor_dev"
#define DEV_NUM 243

MODULE_LICENSE("GPL");

int motor_open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "OPEN motor device\n");
	int i;
	gpio_request(MOTOR, "MOTOR");
	gpio_direction_output(MOTOR, 1);

	for(i = 0; i < 30; i++){
	  gpio_set_value(MOTOR, 1);
	  mdelay(3);
	  gpio_set_value(MOTOR, 0);
	  mdelay(17);
	}	
	return 0;
}

int motor_close(struct inode *pinode, struct file *pfile){// <-> open
	printk(KERN_ALERT "RELEASE motor device\n");
	int i;
	for(i = 0; i < 30; i++){
	  gpio_set_value(MOTOR, 1);
	  mdelay(3);
	  gpio_set_value(MOTOR, 0);
	  mdelay(17);
	}	
	return 0;
}

ssize_t motor_write(struct file *pfile, const char *buffer, size_t length, loff_t *offset){
	printk("Write motor sensor\n");
        int i;
	
	for(i = 0; i < 30; i++){	
	  gpio_set_value(MOTOR, 1);
	  mdelay(2);
	  gpio_set_value(MOTOR, 0);
	  mdelay(18);
	}

	return length;
}

struct file_operations fop = {
	.owner = THIS_MODULE,
	.open = motor_open,
	.write = motor_write,
	.release = motor_close,

};

int __init motor_init(void){
	printk(KERN_ALERT "INIT motor device\n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);
	
	return 0;
}
void __exit motor_exit(void){
	printk(KERN_ALERT "exit motor device\n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}


module_init(motor_init);
module_exit(motor_exit);
