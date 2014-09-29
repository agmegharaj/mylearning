#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h> /*this is the file structure, file open read close */
#include<linux/cdev.h> /* this is for character device, makes cdev avilable*/
#include<linux/semaphore.h> /* this is for the semaphore*/
#include<linux/uaccess.h> /*this is for copy_user vice vers*/

int chardev_init(void);
void chardev_exit(void);
static int device_open(struct inode *, struct file *);
static int device_close(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

/*new code*/
#define BUFFER_SIZE 1024
static char device_buffer[BUFFER_SIZE];
static char *buff_rptr = device_buffer;
static char *buff_wptr = device_buffer;
struct semaphore sem;
struct cdev *mcdev; /*this is the name of my char driver that i will be registering*/
int major_number; /* will store the major number extracted by dev_t*/
int ret; /*used to return values*/
dev_t dev_num; /*will hold the major number that the kernel gives*/

#define DEVICENAME "megharajchard"

/*inode reffers to the actual file on disk*/
static int device_open(struct inode *inode, struct file *filp) {
	if(down_interruptible(&sem) != 0) {
		printk(KERN_ALERT "megharajchard : the device has been opened by some other device, unable to open lock\n");
		return -1;
	}
	//buff_rptr = buff_wptr = device_buffer;
	printk(KERN_INFO "megharajchard : device opened succesfully\n");
	return 0;
}

static ssize_t device_read(struct file *fp, char *buff, size_t length, loff_t *offset) {
	int bytes_read = strlen(buff_rptr);
	if(bytes_read > length) bytes_read = length;
	ret = copy_to_user(buff, buff_rptr, bytes_read);
	buff_rptr += bytes_read;
	printk(KERN_INFO "megharajchard : device has been read\n");
	return bytes_read;
}

static ssize_t device_write(struct file *fp, const char *buff, size_t length, loff_t *offset) {
	int bytes_written = BUFFER_SIZE - (buff_wptr - device_buffer);
	if(bytes_written > length) bytes_written = length;
	ret = copy_from_user(buff_wptr, buff, bytes_written);
	buff_wptr += bytes_written;
	printk(KERN_INFO "megharajchard : device has been written\n");
	return bytes_written;
}
static int device_close(struct inode *inode, struct file *filp) {
	up(&sem);
	printk(KERN_INFO "megharajchard : device has been closed\n");
	return ret;
}

struct file_operations fops = { /* these are the file operations provided by our driver */
	.owner = THIS_MODULE, /*prevents unloading when operations are in use*/
	.open = device_open,  /*to open the device*/
	.write = device_write, /*to write to the device*/
	.read = device_read, /*to read the device*/
	.release = device_close /*to close the device*/
};


int chardev_init(void) 
{
	/* we will get the major number dynamically this is recommended please read ldd3*/
	ret = alloc_chrdev_region(&dev_num,0,1,DEVICENAME);
	if(ret < 0) {
		printk(KERN_ALERT " megharajchard : failed to allocate major number\n");
		return ret;
	}
	else
		printk(KERN_INFO " megharajchard : mjor number allocated succesful\n");
	major_number = MAJOR(dev_num);
	printk(KERN_INFO "megharajchard : major number of our device is %d\n",major_number);
	printk(KERN_INFO "megharajchard : to use mknod /dev/%s c %d 0\n",DEVICENAME,major_number);
	
	mcdev = cdev_alloc(); /*create, allocate and initialize our cdev structure*/
	mcdev->ops = &fops;   /*fops stand for our file operations*/
	mcdev->owner = THIS_MODULE;

	/*we have created and initialized our cdev structure now we need to add it to the kernel*/
	ret = cdev_add(mcdev,dev_num,1);
	if(ret < 0) {
		printk(KERN_ALERT "megharajchard : device adding to the kerknel failed\n");
		return ret;
	}
	else
		printk(KERN_INFO "megharajchard : device additin to the kernel succesful\n");
	sema_init(&sem,1);  /* initial value to one*/
	
	return 0;
}

void chardev_exit(void)
{
	cdev_del(mcdev); /*removing the structure that we added previously*/
	printk(KERN_INFO " megharajchard : removed the mcdev from kernel\n");

	unregister_chrdev_region(dev_num,1);
	printk(KERN_INFO "megharajchard : unregistered the device numbers\n");
	printk(KERN_ALERT " megharajchard : character driver is exiting\n");
}
	
module_init(chardev_init);
module_exit(chardev_exit);

