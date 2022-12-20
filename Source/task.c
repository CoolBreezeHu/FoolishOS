/**************************************************************************//**
 * @file     	task.c
 * @brief    	������غ���
 *
 * @author   	huxing
 * @version  	V0.0.4
 * @date     	2022-11-4 15:21:12
 ******************************************************************************/
#include "ARMCM3.h"
#include "public.h"
#include "task.h"

Task_t *currentTask;	/*! ��ǰ���񣺼�¼��ǰ���ĸ������������� */
Task_t *nextTask;		/*! �л����񣺼�¼׼���л��������� */
Task_t *taskTable[2];	/*! �����б��洢���е����� */

/**
 * @param		task	����
 * @param		entry	�������ں���
 * @param		param	�������ں�������
 * @stack		stack	����ʹ�õĶ�ջ�ռ�
 * @brief		�����ʼ������
 */
void taskInit(Task_t *task, taskFunc_t entry, void *param, uint32_t * stack)
{
	*(--stack) = (uint32_t)(1 << 24);	// XPSR		: ����Thumbģʽ
	*(--stack) = (uint32_t)entry;		// PC		: �������ڵ�ַ
	*(--stack) = (uint32_t)0x14;		// R14(LR)	: δʹ�ã���Ϊ���񲻻�ͨ��return�����Լ�
	*(--stack) = (uint32_t)0x12;		// R12		: δʹ��
	*(--stack) = (uint32_t)0x3;			// R3		: δʹ��
	*(--stack) = (uint32_t)0x2;			// R2		: δʹ��
	*(--stack) = (uint32_t)0x1;			// R1		: δʹ�ã���Ϊ����ֻ��һ������
	*(--stack) = (uint32_t)param;		// R0		: ����ĵ�һ������
	
	*(--stack) = (uint32_t)0x11;		// R11		: δʹ��
	*(--stack) = (uint32_t)0x10;		// R10		: δʹ��
	*(--stack) = (uint32_t)0x9;			// R9		: δʹ��
	*(--stack) = (uint32_t)0x8;			// R8		: δʹ��
	*(--stack) = (uint32_t)0x7;			// R7		: δʹ��
	*(--stack) = (uint32_t)0x6;			// R6		: δʹ��
	*(--stack) = (uint32_t)0x5;			// R5		: δʹ��
	*(--stack) = (uint32_t)0x4;			// R4		: δʹ��
	
	task->stack = stack;
}

/**
 * @brief		�����л�����
 * 
 * ����һ�������л���LotusOS�������ú�currentTask��nextTask��Ȼ����øú����л�������nextTask����
 */
void taskSwitch(void)
{
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

/**
 * @brief		������Ⱥ���
 * 
 * ͨ���Զ���ĵ����㷨��ѡ����һ�����е�����Ȼ���л���ȥ
 */
void taskSched(void)
{
	if (currentTask == taskTable[0]) {
		nextTask = taskTable[1];
	} else {
		nextTask = taskTable[0];
	}
	taskSwitch();
}

/**
 * @brief		���øú��������л�����һ����������
 */
void taskRunFirst(void)
{
	__set_PSP(0);
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}
