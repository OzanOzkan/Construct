###########################
#
# AndroidLauncher shared library
#
###########################

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ENGINE_ROOT_PATH := F:/Development/ProjectO01
ENGINE_CODE_PATH := $(ENGINE_ROOT_PATH)/Code
ENGINE_SDK_PATH := $(ENGINE_ROOT_PATH)/SDKs.old

LOCAL_MODULE := main

LOCAL_CPP_FEATURES += exceptions

SDL_PATH := $(ENGINE_SDK_PATH)/SDL2-2.0.10
SDL_MODULES_PATH := $(SDL_PATH)/modules

LOCAL_C_INCLUDES := $(SDL_PATH)/include
LOCAL_C_INCLUDES += $(ENGINE_CODE_PATH)/Common

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)

# SDL2
SUPPORT_JPG := true
SUPPORT_PNG := true
SUPPORT_WEBP := false
include $(SDL_PATH)/Android.mk
include $(SDL_MODULES_PATH)/SDL2_image-2.0.5/Android.mk
include $(SDL_MODULES_PATH)/SDL2_ttf-2.0.15/Android.mk
# ~SDL2

# Engine Source
include $(ENGINE_CODE_PATH)/Android.mk
# ~Engine Source
