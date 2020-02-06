#include "neoway_openplatform.h"
/*link output symble definitions*/
extern U32 Load$$APP_RAM_RW$$Base, Image$$APP_RAM_RW$$Base, Image$$APP_RAM_RW$$Length, Image$$APP_RAM_RW$$ZI$$Base, Image$$APP_RAM_RW$$ZI$$Length;
extern U32 Load$$CODE_ROM_USER$$Base, Image$$CODE_ROM_USER$$Base, Image$$CODE_ROM_USER$$Length;
extern U32 Load$$PLATFORM_INIT_ROM$$Base, Image$$PLATFORM_INIT_ROM$$Base, Image$$PLATFORM_INIT_ROM$$Length;
extern U32 Load$$MAIN_APP$$Base, Image$$MAIN_APP$$Base, Image$$MAIN_APP$$Length;

extern void NWT_memset(U8*dst,U8 data,U32 len);
extern void neoway_get_addr(void);
extern void Neoway_UserInit(void);
extern void Neoway_RegisterCallbackFunction(void);

#pragma arm section rodata = "start_custom_app"
/*Note: users are not allowed to add their own functions before the neo_entry function*/
U8 HEAD_Stack[100];/*Define the HEAD space of the C runtime*/
void neo_entry(void)
{
    NWT_memset((U8*)&Image$$APP_RAM_RW$$ZI$$Base,0, (U32)&Image$$APP_RAM_RW$$ZI$$Length);
    neoway_get_addr();
    __rt_lib_init((U32)&HEAD_Stack[0],(U32)&(HEAD_Stack[sizeof(HEAD_Stack)-1]));/*Initializes the user's C runtime, otherwise the C runtime calls the interface incorrectly*/ 
    Neoway_RegisterCallbackFunction();
    Neoway_UserInit();
}

#pragma arm section rodata