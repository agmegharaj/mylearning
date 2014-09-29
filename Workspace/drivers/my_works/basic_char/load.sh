#!/bin/sh

sudo insmod megharajchard.ko
sudo mknod /dev/megharajchard c 251 0
sudo chmod 777 /dev/megharajchard

