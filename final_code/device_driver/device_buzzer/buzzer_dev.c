#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define buzzer_gpio	18			
#define DEV_NAME	"buzzer_dev"
#define DEV_NUM 	241

MODULE_LICENSE("GPL");

int buzzer_open(struct inode *minode, struct file *mfile){
	
	printk(KERN_ALERT "OPEN buzzer_dev\n");
	gpio_request(buzzer_gpio, "buzzer_gpio");
	gpio_direction_output(buzzer_gpio, 1);
	return 0;
}

int buzzer_release(struct inode *minode, struct file *mfile){
	
	printk(KERN_ALERT "Release buzzer_dev\n");
	return 0;
}

ssize_t buzzer_write(struct file *minode,const char *buffer,size_t length,loff_t *offset){
	printk(KERN_ALERT "WRITE PITCH");
	int i=0;
	unsigned char *addr;
	unsigned char c;

	//get_user(c,buffer);
	//int freq=atoi(c);
	//int halfPeriod=
	// write 호출시 삐이~~ 소리나는거.. ㅋㅋ

	for(i=0;i<1000;i++){
	   gpio_set_value(buzzer_gpio, 1);
	   udelay(230);
	   gpio_set_value(buzzer_gpio, 0);
	   udelay(230);
	}

	return length;
}

struct file_operations fop ={
	.owner = THIS_MODULE,
	.open = buzzer_open,
	.release = buzzer_release,
	.write = buzzer_write,
};

int buzzer_init(void){
	int result;

	result = register_chrdev(DEV_NUM, DEV_NAME, &fop);
	printk(KERN_ALERT "Init Module, Buzzer Major number : %d\n", DEV_NUM);
	return 0;
}

void buzzer_exit(void){
	unregister_chrdev(DEV_NUM, DEV_NAME);
	printk(KERN_ALERT "DRIVER EXIT\n");
}

module_init(buzzer_init);
module_exit(buzzer_exit);
