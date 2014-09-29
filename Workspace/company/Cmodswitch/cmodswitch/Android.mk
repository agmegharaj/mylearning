LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= usb_modeswitch.c
LOCAL_MODULE := cmodswitch
LOCAL_SHARED_LIBRARIES := libc liblog libusbhost
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
