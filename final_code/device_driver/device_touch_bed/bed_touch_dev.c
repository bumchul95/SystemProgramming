#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define bed_gpio 23  //gpio 4
#define DEV_NAME "bed_touch_dev"
#define DEV_NUM 240

MODULE_LICENSE("GPL");

int touch_open(struct inode *pinode, struct file *pfile) {
	printk(KERN_ALERT "OPEN bed_touch_dev\n");

	int ret = gpio_request(bed_gpio, "bed_gpio");
	gpio_direction_input(bed_gpio);

	printk(KERN_ALERT "request : %d\n", ret);

	return 0;
}

int touch_close(struct inode *pinode, struct file *pfile) {
	
	printk(KERN_ALERT "RELEASE bed_touch_dev\n");
	
	return 0;
}

ssize_t touch_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	
	printk("Read bed_touch_sensor\n");
	
	int result;
	int stat;

	stat = gpio_get_value(bed_gpio);
	result = copy_to_user(buffer, &stat, sizeof(stat));
	printk("bed_touch sensor's value : %d\n", stat);

	return 0;
}

struct file_operations fop = {
	.owner = THIS_MODULE,
	.open = touch_open,
	.release = touch_close,
	.read = touch_read,
};

int __init touch_init(void){
	printk(KERN_ALERT "INIT bed_touch_dev\n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);
	
	return 0;
}

void __exit touch_exit(void) {
	printk(KERN_ALERT "EXIT bed_touch_dev\n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}

module_init(touch_init);
module_exit(touch_exit);
