###########################
#
# Plugins shared library
#
###########################

LOCAL_MODULE := BokPlugins
LOCAL_MODULE_FILENAME := libBokPlugins
MODULE_DIR := $(call my-dir)

LOCAL_CPPFLAGS += -std=c++17
LOCAL_C_INCLUDES += $(ENGINE_CODE_PATH)/Common

LOCAL_SRC_FILES := \
	$(wildcard $(MODULE_DIR)/EntityComponents/*.cpp) \
	$(wildcard $(MODULE_DIR)/*.cpp)

LOCAL_CFLAGS += \
	-Wno-unused-parameter \
	-Wno-sign-compare \
	-Wno-switch \
	-Wno-missing-prototypes \
	-Wno-unused-value \
	-Wno-incompatible-pointer-types\
	-Wno-float-conversion \
	-Wunused-private-field

include $(BUILD_STATIC_LIBRARY)
