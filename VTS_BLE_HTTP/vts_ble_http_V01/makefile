
#-------------------------------------------------------------------------------
# config tools, tool path
#-------------------------------------------------------------------------------
ARMTOOL_PATH=C:\Progra~1\ARM\RVCT


#-------------------------------------------------------------------------------
# config version
#-------------------------------------------------------------------------------
PLATFORM=NEOWAY
BUILD=CUSTOM
VERSION=V01

include .\makefiledef
#-------------------------------------------------------------------------------
# config build dir
#-------------------------------------------------------------------------------
#BUILD_DIRS=customer example
BUILD_DIRS= example


all:
	@$(MAKE) help

help:	
	@echo **********************help*******************
	@echo  please you input following command to make example
	@echo  make helloworld
	@echo  make custom
	@echo  make at
	@echo  make gpio
	@echo  make eint
	@echo  make flash
	@echo  make memory
	@echo  make pwm
	@echo  make clk
	@echo  make alert
	@echo  make keyboard
	@echo  make lcd
	@echo  make i2c
	@echo  make file
	@echo  make audio
	@echo  make transpass
	@echo  make tcpip
	@echo  make multitask
	@echo  make multitask_port
	@echo  make sms
	@echo  make headset
	@echo  make lcm_st7545t
	@echo  make lcm_uc1701
	@echo  make tcplong
	@echo  make multimemory
	@echo  make lowrateuart
	@echo  make eintcallback
	@echo  make fota         [only for FLASH=TOSB 128Mb+32Mb]

helloworld:
	@echo *******make helloworld*********
	@echo -D__EXAMPLE_HELLWORLD__ > .\$(DEFVIATMP)
	@$(MAKE) clean
	@$(MAKE) new

	


export ARMTOOL_PATH
	
