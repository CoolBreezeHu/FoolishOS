/**************************************************************************//**
 * @file     	pendsvc.c
 * @brief    	PendSVC������
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
 * @brief    	PendSVC�쳣������
 * @see      	triggerPendSVC
 */
__asm void PendSV_Handler ()
{
	IMPORT currentTask
	IMPORT nextTask
	
	// �����ں˼Ĵ�����ֵ��currentTask�������ջ
	MRS		R0, PSP				// ��ȡPSP��ֵ����ȡcurrentTask�Ķ�ջָ��
	CBZ		R0, nosave			// �ж�PSP��ֵ�Ƿ�Ϊ0��0��taskRunFirst����    ��0��taskSwitch����
	
	STMDB	R0!, {R4-R11}		
	
	LDR		R1, =currentTask
	LDR 	R1, [R1]
	STR     R0, [R1]			// currentTask->stack = PSP;
nosave
	// ʹ��nextTask����currentTask������nextTask�Ķ�ջ����ͬ�����ں˼Ĵ���
	LDR		R0, =currentTask
	LDR		R1, =nextTask
	LDR		R2, [R1]
	STR  	R2, [R0]			// R0 = currentTask = nextTask
	
	LDR  	R0, [R2]			// R2 = *nextTask ==> R0 = *(nextTask->stack)
	LDMIA  	R0!, {R4-R11}		// �ָ�{R4, R11}���������˳�PendSVʱ��Ӳ���Զ��ָ�
	
	MSR		PSP, R0				// PSP = R0;
	ORR 	LR, LR, #0x04		// ����·��ر�ǣ�ָ�����˳�LRʱ���л���PSP��ջ��(PendSVʹ�õ���MSP) 
	BX		LR
}
