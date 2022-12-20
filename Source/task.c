/**************************************************************************//**
 * @file     	task.c
 * @brief    	任务相关函数
 *
 * @author   	huxing
 * @version  	V0.0.4
 * @date     	2022-11-4 15:21:12
 ******************************************************************************/
#include "ARMCM3.h"
#include "public.h"
#include "task.h"

Task_t *currentTask;	/*! 当前任务：记录当前是哪个任务正在运行 */
Task_t *nextTask;		/*! 切换任务：记录准备切换到的任务 */
Task_t *taskTable[2];	/*! 任务列表：存储所有的任务 */

/**
 * @param		task	任务
 * @param		entry	任务的入口函数
 * @param		param	任务的入口函数参数
 * @stack		stack	任务使用的堆栈空间
 * @brief		任务初始化函数
 */
void taskInit(Task_t *task, taskFunc_t entry, void *param, uint32_t * stack)
{
	*(--stack) = (uint32_t)(1 << 24);	// XPSR		: 开启Thumb模式
	*(--stack) = (uint32_t)entry;		// PC		: 任务的入口地址
	*(--stack) = (uint32_t)0x14;		// R14(LR)	: 未使用，因为任务不会通过return结束自己
	*(--stack) = (uint32_t)0x12;		// R12		: 未使用
	*(--stack) = (uint32_t)0x3;			// R3		: 未使用
	*(--stack) = (uint32_t)0x2;			// R2		: 未使用
	*(--stack) = (uint32_t)0x1;			// R1		: 未使用，因为任务只有一个参数
	*(--stack) = (uint32_t)param;		// R0		: 任务的第一个参数
	
	*(--stack) = (uint32_t)0x11;		// R11		: 未使用
	*(--stack) = (uint32_t)0x10;		// R10		: 未使用
	*(--stack) = (uint32_t)0x9;			// R9		: 未使用
	*(--stack) = (uint32_t)0x8;			// R8		: 未使用
	*(--stack) = (uint32_t)0x7;			// R7		: 未使用
	*(--stack) = (uint32_t)0x6;			// R6		: 未使用
	*(--stack) = (uint32_t)0x5;			// R5		: 未使用
	*(--stack) = (uint32_t)0x4;			// R4		: 未使用
	
	task->stack = stack;
}

/**
 * @brief		任务切换函数
 * 
 * 进行一次任务切换。LotusOS会先配置好currentTask和nextTask，然后调用该函数切换任务至nextTask运行
 */
void taskSwitch(void)
{
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

/**
 * @brief		任务调度函数
 * 
 * 通过自定义的调度算法，选择下一个运行的任务，然后切换过去
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
 * @brief		调用该函数，将切换至第一个任务运行
 */
void taskRunFirst(void)
{
	__set_PSP(0);
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}
