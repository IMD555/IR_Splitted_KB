#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Configuration.mk)" "nbproject/Makefile-local-Configuration.mk"
include nbproject/Makefile-local-Configuration.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Configuration
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/IR_Splitted_Master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/IR_Splitted_Master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=leds.c buttons.c usb_device.c usb_descriptors.c usb_device_hid.c usb_events.c usb_hal_16bit.c system.c app_device_keyboard.c main.c app_led_usb_status.c ringBuffer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/leds.o ${OBJECTDIR}/buttons.o ${OBJECTDIR}/usb_device.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_device_hid.o ${OBJECTDIR}/usb_events.o ${OBJECTDIR}/usb_hal_16bit.o ${OBJECTDIR}/system.o ${OBJECTDIR}/app_device_keyboard.o ${OBJECTDIR}/main.o ${OBJECTDIR}/app_led_usb_status.o ${OBJECTDIR}/ringBuffer.o
POSSIBLE_DEPFILES=${OBJECTDIR}/leds.o.d ${OBJECTDIR}/buttons.o.d ${OBJECTDIR}/usb_device.o.d ${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/usb_device_hid.o.d ${OBJECTDIR}/usb_events.o.d ${OBJECTDIR}/usb_hal_16bit.o.d ${OBJECTDIR}/system.o.d ${OBJECTDIR}/app_device_keyboard.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/app_led_usb_status.o.d ${OBJECTDIR}/ringBuffer.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/leds.o ${OBJECTDIR}/buttons.o ${OBJECTDIR}/usb_device.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_device_hid.o ${OBJECTDIR}/usb_events.o ${OBJECTDIR}/usb_hal_16bit.o ${OBJECTDIR}/system.o ${OBJECTDIR}/app_device_keyboard.o ${OBJECTDIR}/main.o ${OBJECTDIR}/app_led_usb_status.o ${OBJECTDIR}/ringBuffer.o

# Source Files
SOURCEFILES=leds.c buttons.c usb_device.c usb_descriptors.c usb_device_hid.c usb_events.c usb_hal_16bit.c system.c app_device_keyboard.c main.c app_led_usb_status.c ringBuffer.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Configuration.mk dist/${CND_CONF}/${IMAGE_TYPE}/IR_Splitted_Master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GB202
MP_LINKER_FILE_OPTION=,--script=p24FJ64GB202.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/leds.o: leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/leds.o.d 
	@${RM} ${OBJECTDIR}/leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  leds.c  -o ${OBJECTDIR}/leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/leds.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/leds.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/buttons.o: buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.o.d 
	@${RM} ${OBJECTDIR}/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  buttons.c  -o ${OBJECTDIR}/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/buttons.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/buttons.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_device.o: usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_device.c  -o ${OBJECTDIR}/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_device.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_descriptors.c  -o ${OBJECTDIR}/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_device_hid.o: usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/usb_device_hid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_device_hid.c  -o ${OBJECTDIR}/usb_device_hid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_device_hid.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_device_hid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_events.o: usb_events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_events.o.d 
	@${RM} ${OBJECTDIR}/usb_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_events.c  -o ${OBJECTDIR}/usb_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_events.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_events.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_hal_16bit.o: usb_hal_16bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_hal_16bit.c  -o ${OBJECTDIR}/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_hal_16bit.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_hal_16bit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/app_device_keyboard.o: app_device_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_device_keyboard.o.d 
	@${RM} ${OBJECTDIR}/app_device_keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app_device_keyboard.c  -o ${OBJECTDIR}/app_device_keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app_device_keyboard.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/app_device_keyboard.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/app_led_usb_status.o: app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_led_usb_status.o.d 
	@${RM} ${OBJECTDIR}/app_led_usb_status.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app_led_usb_status.c  -o ${OBJECTDIR}/app_led_usb_status.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app_led_usb_status.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/app_led_usb_status.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ringBuffer.o: ringBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ringBuffer.o.d 
	@${RM} ${OBJECTDIR}/ringBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ringBuffer.c  -o ${OBJECTDIR}/ringBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ringBuffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/ringBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/leds.o: leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/leds.o.d 
	@${RM} ${OBJECTDIR}/leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  leds.c  -o ${OBJECTDIR}/leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/leds.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/leds.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/buttons.o: buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/buttons.o.d 
	@${RM} ${OBJECTDIR}/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  buttons.c  -o ${OBJECTDIR}/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/buttons.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/buttons.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_device.o: usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_device.c  -o ${OBJECTDIR}/usb_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_device.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_descriptors.c  -o ${OBJECTDIR}/usb_descriptors.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_device_hid.o: usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/usb_device_hid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_device_hid.c  -o ${OBJECTDIR}/usb_device_hid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_device_hid.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_device_hid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_events.o: usb_events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_events.o.d 
	@${RM} ${OBJECTDIR}/usb_events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_events.c  -o ${OBJECTDIR}/usb_events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_events.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_events.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/usb_hal_16bit.o: usb_hal_16bit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_hal_16bit.o.d 
	@${RM} ${OBJECTDIR}/usb_hal_16bit.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  usb_hal_16bit.c  -o ${OBJECTDIR}/usb_hal_16bit.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_hal_16bit.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/usb_hal_16bit.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/app_device_keyboard.o: app_device_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_device_keyboard.o.d 
	@${RM} ${OBJECTDIR}/app_device_keyboard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app_device_keyboard.c  -o ${OBJECTDIR}/app_device_keyboard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app_device_keyboard.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/app_device_keyboard.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/app_led_usb_status.o: app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/app_led_usb_status.o.d 
	@${RM} ${OBJECTDIR}/app_led_usb_status.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  app_led_usb_status.c  -o ${OBJECTDIR}/app_led_usb_status.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/app_led_usb_status.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/app_led_usb_status.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ringBuffer.o: ringBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ringBuffer.o.d 
	@${RM} ${OBJECTDIR}/ringBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ringBuffer.c  -o ${OBJECTDIR}/ringBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ringBuffer.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -falign-arrays -I"." -msmart-io=1 -Wall -msfr-warn=off   -std=c99
	@${FIXDEPS} "${OBJECTDIR}/ringBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/IR_Splitted_Master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/IR_Splitted_Master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/IR_Splitted_Master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/IR_Splitted_Master.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_Configuration=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/IR_Splitted_Master.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Configuration
	${RM} -r dist/Configuration

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
