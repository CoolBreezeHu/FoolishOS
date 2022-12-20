/**************************************************************************//**
 * @file     	pendsvc.c
 * @brief    	PendSVC处理函数
 *
 * @author   	huxing
 * @version  	V0.0.4
 * @date     	2022-11-4 13:54:01
 ******************************************************************************/
#include "ARMCM3.h"
#include "public.h"
#include "pendsvc.h"
#include "task.h"

/**
 * @fn			__asm void PendSV_Handler ()	
 * @brief    	PendSVC异常处理函数
 * @see      	triggerPendSVC
 */
__asm void PendSV_Handler ()
{
	IMPORT currentTask
	IMPORT nextTask
	
	// 保存内核寄存器的值到currentTask的任务堆栈
	MRS		R0, PSP				// 读取PSP的值，获取currentTask的堆栈指针
	CBZ		R0, nosave			// 判断PSP的值是否为0；0：taskRunFirst触发    非0：taskSwitch触发
	
	STMDB	R0!, {R4-R11}		
	
	LDR		R1, =currentTask
	LDR 	R1, [R1]
	STR     R0, [R1]			// currentTask->stack = PSP;
nosave
	// 使用nextTask更新currentTask，并将nextTask的堆栈数据同步到内核寄存器
	LDR		R0, =currentTask
	LDR		R1, =nextTask
	LDR		R2, [R1]
	STR  	R2, [R0]			// R0 = currentTask = nextTask
	
	LDR  	R0, [R2]			// R2 = *nextTask ==> R0 = *(nextTask->stack)
	LDMIA  	R0!, {R4-R11}		// 恢复{R4, R11}，其余在退出PendSV时，硬件自动恢复
	
	MSR		PSP, R0				// PSP = R0;
	ORR 	LR, LR, #0x04		// 标记下返回标记，指明在退出LR时，切换到PSP堆栈中(PendSV使用的是MSP) 
	BX		LR
}
