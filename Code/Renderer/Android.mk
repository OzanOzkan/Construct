###########################
#
# Renderer shared library
#
###########################

LOCAL_MODULE := BokRenderer
LOCAL_MODULE_FILENAME := libBokRenderer
MODULE_DIR := $(call my-dir)

LOCAL_CPPFLAGS += -std=c++17
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES += $(ENGINE_CODE_PATH)/Common

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(MODULE_DIR)/SDLRenderer/RendererObject/*.cpp) \
	$(wildcard $(MODULE_DIR)/SDLRenderer/*.cpp) \
	$(wildcard $(MODULE_DIR)/*.cpp))

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf

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
