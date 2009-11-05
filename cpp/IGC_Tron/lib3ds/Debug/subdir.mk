################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib3ds_atmosphere.c \
../lib3ds_background.c \
../lib3ds_camera.c \
../lib3ds_chunk.c \
../lib3ds_chunktable.c \
../lib3ds_file.c \
../lib3ds_io.c \
../lib3ds_light.c \
../lib3ds_material.c \
../lib3ds_math.c \
../lib3ds_matrix.c \
../lib3ds_mesh.c \
../lib3ds_node.c \
../lib3ds_quat.c \
../lib3ds_shadow.c \
../lib3ds_track.c \
../lib3ds_util.c \
../lib3ds_vector.c \
../lib3ds_viewport.c 

OBJS += \
./lib3ds_atmosphere.o \
./lib3ds_background.o \
./lib3ds_camera.o \
./lib3ds_chunk.o \
./lib3ds_chunktable.o \
./lib3ds_file.o \
./lib3ds_io.o \
./lib3ds_light.o \
./lib3ds_material.o \
./lib3ds_math.o \
./lib3ds_matrix.o \
./lib3ds_mesh.o \
./lib3ds_node.o \
./lib3ds_quat.o \
./lib3ds_shadow.o \
./lib3ds_track.o \
./lib3ds_util.o \
./lib3ds_vector.o \
./lib3ds_viewport.o 

C_DEPS += \
./lib3ds_atmosphere.d \
./lib3ds_background.d \
./lib3ds_camera.d \
./lib3ds_chunk.d \
./lib3ds_chunktable.d \
./lib3ds_file.d \
./lib3ds_io.d \
./lib3ds_light.d \
./lib3ds_material.d \
./lib3ds_math.d \
./lib3ds_matrix.d \
./lib3ds_mesh.d \
./lib3ds_node.d \
./lib3ds_quat.d \
./lib3ds_shadow.d \
./lib3ds_track.d \
./lib3ds_util.d \
./lib3ds_vector.d \
./lib3ds_viewport.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


