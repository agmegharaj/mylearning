#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h> /*this is the file structure, file open read close */
#include<linux/cdev.h> /* this is for character device, makes cdev avilable*/
#include<linux/semaphore.h> /* this is for the semaphore*/
#include<linux/uaccess.h> /*this is for copy_user vice vers*/
#include<linux/proc_fs.h>

#define MAX_LEN 1024
int read_info(char *page, char **start, off_t off,  int count, int *eof, void *data);
int write_info(struct file *filp, const char __user *buffer, unsigned long length, void *data);
int proc_init(void);
void proc_clean(void);


static struct proc_dir_entry *proc_entry;
static char *info;
static int write_index;
static int read_index;

int write_info(struct file *filp, const char __user *buffer, unsigned long length, void *data) {
	int capacity = (MAX_LEN - write_index) +1;
	if(length > capacity) {
		printk(KERN_INFO "NO sapce to write into peoc file \n");
		return -1;
	}
	if(copy_from_user(&info[write_index], buffer, length)) 
		return -2;
	write_index += length;
	printk(KERN_INFO " megharaj proc writing succesful, %d write \n", length);
	return length;
}

int read_info(char *page, char **start, off_t off, int count, int *eof, void *data) {
	int len;
	len = sprintf(page, "%s\n", &info[read_index]);
	read_index += len;
	printk(KERN_INFO " megharaj proc reading succesful, %d read \n", len);
	return len;
}
	

int proc_init(void) 
{
	int ret = 0;
	info = (char *)vmalloc(MAX_LEN);
	memset(info, 0 , MAX_LEN);
/*truct proc_dir_entry *create_proc_entry(const char *name, mode_t mode,
                                         struct proc_dir_entry *parent);*/
	proc_entry = create_proc_entry("/proc/sys/megharaj_proc", 0666, NULL);
	if(proc_entry == NULL) {
		vfree(info);
		printk(KERN_INFO " megharaj proc not created \n");
		ret = -ENOMEM;
	}
	else {
		write_index = 0;
		read_index = 0;
		proc_entry->read_proc = read_info;
		proc_entry->write_proc = write_info;
		printk(KERN_INFO " megharaj proc created \n");
	}
	return ret;
}

void proc_clean(void) 
{
	vfree(info);
	remove_proc_entry("megharaj_proc", NULL);
	
}

MODULE_LICENSE("GPL");   
module_init(proc_init);
module_exit(proc_clean);

		
	
	





