#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define PIR 24  //gpio 5
#define DEV_NAME "servo_dev"
#define DEV_NUM 241

MODULE_LICENSE("GPL");

int servo_open(struct inode *pinode, struct file *pfile) {
	printk(KERN_ALERT "OPEN servo_dev\n");

	gpio_request(PIR, "PIR");
	gpio_direction_input(PIR);

	return 0;
}

int servo_close(struct inode *pinode, struct file *pfile) {
	
	printk(KERN_ALERT "RELEASE servo_dev\n");
	
	return 0;
}

ssize_t servo_write(struct file *pfile, const char __user *buffer ,size_t length, loff_t *offset){
	
	printk("servo touch_sensor\n");

	return 0;
}

ssize_t servo_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	
	printk("Read servo_sensor\n");
	
	int result;
	int stat;

	stat = gpio_get_value(PIR);
	result = copy_to_user(buffer, &stat, sizeof(stat));

	return 0;
}


struct file_operations fop = {
	.owner = THIS_MODULE,
	.open = servo_open,
	.release = servo_close,
	.write = servo_write,
	.read = servo_read,
};

int __init touch_init(void){
	printk(KERN_ALERT "INIT touch_dev\n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);
	
	return 0;
}

void __exit touch_exit(void) {
	printk(KERN_ALERT "EXIT touch_dev\n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}

module_init(touch_init);
module_exit(touch_exit);
