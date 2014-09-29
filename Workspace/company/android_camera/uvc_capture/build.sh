#!/bin/sh

rm uvccap.o uvccap_main.o uvccap 
ls -tl
/usr/android-toolchain-eabi/bin/arm-linux-androideabi-gcc -Werror -O2 -I/home/nowon/sumit/ndk/android-ndk-r7/platforms/android-14/arch-arm/usr/include -c uvccap.c

/usr/android-toolchain-eabi/bin/arm-linux-androideabi-gcc -Werror -O2 -I/home/nowon/sumit/ndk/android-ndk-r7/platforms/android-14/arch-arm/usr/include -c uvccap_main.c
ls -tl

/usr/android-toolchain-eabi/bin/arm-linux-androideabi-ld -nostdlib --entry=_start --dynamic-linker /system/bin/linker -rpath /system/lib -L/home/nowon/sumit/ndk/android-ndk-r7/platforms/android-14/arch-arm/usr/lib -lc -lstdc++ uvccap_main.o uvccap.o -o uvccap
#/usr/android-toolchain-eabi/bin/arm-linux-androideabi-ld -nostdlib --dynamic-linker /system/bin/linker -rpath /system/lib -L/home/nowon/sumit/prebuilts/ndk/android-ndk-r7/platforms/android-14/arch-arm/usr/lib -lc -lstdc++ uvccap_main.o uvccap.o -o uvccap

ls -tl


/home/nowon/Workspace/Android_toolchain/linaro-4.7-201207/android-toolchain-eabi/bin/arm-linux-androideabi-gcc -Werror -O2 -I/home/nowon/Workspace/pandroid-linaro-tracking/prebuilt/ndk/android-ndk-r7/platforms/android-14/arch-arm/usr/include -c usb_modeswitch.c


/home/nowon/Workspace/Android_toolchain/linaro-4.7-201207/android-toolchain-eabi/bin/arm-linux-androideabi-ld -nostdlib --entry=main --dynamic-linker /system/bin/linker -rpath /system/lib -L/home/nowon/Workspace/pandroid-linaro-tracking/prebuilt/ndk/android-ndk-r7/platforms/android-14/arch-arm/usr/lib -lc usb_modeswitch.o -o cusbswitch


