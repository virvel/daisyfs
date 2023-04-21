# Project Name
TARGET = daisyfs

# Sources
CPP_SOURCES = src/frequencyshifter.cpp src/daisyfs.cpp
C_SOURCES = \
$(LIBDAISY_DIR)/Drivers/CMSIS/DSP/Source/FilterFunctions/arm_biquad_cascade_df1_f32.c\
$(LIBDAISY_DIR)/Drivers/CMSIS/DSP/Source/FilterFunctions/arm_biquad_cascade_df1_init_f32.c\
$(LIBDAISY_DIR)/Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.c\
$(LIBDAISY_DIR)/Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.c\
$(LIBDAISY_DIR)/Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.c


# Library Locations
LIBDAISY_DIR = libDaisy
DAISYSP_DIR = DaisySP

C_INCLUDES += \
-I$(LIBDAISY_DIR)/Drivers/CMSIS/DSP/Include 

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
