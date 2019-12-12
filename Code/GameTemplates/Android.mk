###########################
#
# Game shared library
#
###########################

LOCAL_MODULE := BokGame
LOCAL_MODULE_FILENAME := libBokGame
MODULE_DIR := $(call my-dir)

LOCAL_CPPFLAGS += -std=c++17

LOCAL_C_INCLUDES += \
	$(wildcard $(ENGINE_CODE_PATH)/Common) \
	$(wildcard $(ENGINE_CODE_PATH)/Plugins)

LOCAL_SRC_FILES := \
	$(wildcard $(MODULE_DIR)/LookingGlass/EntityComponents/*.cpp) \
	$(wildcard $(MODULE_DIR)/LookingGlass/Player/*.cpp) \
	$(wildcard $(MODULE_DIR)/LookingGlass/*.cpp)

LOCAL_SHARED_LIBRARIES := BokPlugins

LOCAL_CFLAGS += \
	-Wno-unused-parameter \
	-Wno-sign-compare \
	-Wno-switch \
	-Wno-missing-prototypes \
	-Wno-unused-value \
	-Wno-incompatible-pointer-types\
	-Wno-float-conversion \
	-Wunused-private-field

include $(BUILD_SHARED_LIBRARY)
