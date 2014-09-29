#ifndef IOCTL_H
#define IOCTL_H
#include<linux/ioctl.h>

#define IOCTL_MAGIC_NUMBER 100
#define IOCTL_READ _IOR(IOCTL_MAGIC_NUMBER, 0, char *)
#define IOCTL_WRITE _IOW(IOCTL_MAGIC_NUMBER, 1, char *)
#define IOCTL_HELLO _IO(IOCTL_MAGIC_NUMBER, 2)

#define IOCTL_MAGIC_MAX 2

#endif

