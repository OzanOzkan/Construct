###########################
#
# Physics shared library
#
###########################

LOCAL_MODULE := BokPhysics
LOCAL_MODULE_FILENAME := libBokPhysics
MODULE_DIR := $(call my-dir)

LOCAL_CPPFLAGS += -std=c++17
LOCAL_CPP_FEATURES := rtti exceptions

LOCAL_C_INCLUDES := $(ENGINE_CODE_PATH)/Common
LOCAL_C_INCLUDES += $(BOX2D_INCLUDE_PATH)

LOCAL_SRC_FILES := \
  $(wildcard $(MODULE_DIR)/*.cpp) \
  $(wildcard $(MODULE_DIR)/B2DPhysics/*.cpp) \
	$(wildcard $(MODULE_DIR)/B2DPhysics/B2DObject/*.cpp)

LOCAL_SHARED_LIBRARIES := Box2D

LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES

LOCAL_CFLAGS += \
	-Wall -Wextra \
	-Wdocumentation \
	-Wdocumentation-unknown-command \
	-Wmissing-prototypes \
	-Wunreachable-code-break \
	-Wunneeded-internal-declaration \
	-Wmissing-variable-declarations \
	-Wfloat-conversion \
	-Wshorten-64-to-32 \
	-Wunreachable-code-return

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
