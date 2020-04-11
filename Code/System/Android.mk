###########################
#
# System shared library
#
###########################

LOCAL_MODULE := BokSystem
LOCAL_MODULE_FILENAME := libBokSystem
MODULE_DIR := $(call my-dir)

LOCAL_CPPFLAGS += -std=c++17
LOCAL_CPP_FEATURES := rtti exceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES += $(ENGINE_CODE_PATH)/Common

LOCAL_SRC_FILES := \
	$(wildcard $(MODULE_DIR)/EntitySystem/*.cpp) \
	$(wildcard $(MODULE_DIR)/EventSystem/*.cpp) \
	$(wildcard $(MODULE_DIR)/Window/*.cpp) \
	$(wildcard $(MODULE_DIR)/UI/*.cpp)\
	$(wildcard $(MODULE_DIR)/*.cpp)

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES

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
