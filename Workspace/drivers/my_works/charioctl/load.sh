#!/bin/sh

sudo insmod ioctl.ko
sudo mknod /dev/megharajchard c 250 0
sudo chmod 777 /dev/megharajchard

