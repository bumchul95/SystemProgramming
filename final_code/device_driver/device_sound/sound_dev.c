#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define SOUND 5 //gpio 21
#define DEV_NAME "sound_dev"
#define DEV_NUM 236

MODULE_LICENSE("GPL");

int sound_open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "OPEN sound device\n");

	int ret = gpio_request(SOUND, "SOUND");
	gpio_direction_input(SOUND);
	
	return 0;
}

int sound_close(struct inode *pinode, struct file *pfile){// <-> open
	printk(KERN_ALERT "RELEASE sound device\n");

	return 0;
}

ssize_t sound_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	printk("Read sound sensor\n");

	int stat;
	int result;	
	stat = gpio_get_value(SOUND);
	result = copy_to_user(buffer, &stat, sizeof(stat));
	printk("sound sensor's value %d\n", stat);

	return 0;
}

struct file_operations fop = {
	.owner = THIS_MODULE,
	.open = sound_open,
	.read = sound_read,
	.release = sound_close,

};

int __init sound_init(void){
	printk(KERN_ALERT "INIT sound device\n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);

	return 0;
}

void __exit sound_exit(void){
	printk(KERN_ALERT "exit sound device\n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}


module_init(sound_init);
module_exit(sound_exit);
