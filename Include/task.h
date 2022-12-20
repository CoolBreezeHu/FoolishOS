/**************************************************************************//**
 * @file     	task.h
 * @brief    	任务头文件
 *
 * @author   	huxing
 * @version  	V0.0.4
 * @date     	2022-11-4 15:51:45
 ******************************************************************************/
#ifndef __TASK_H_
#define __TASK_H_

#include <stdint.h>	 /*!< 标准头文件，里面包含了常用的类型定义，如：uint32_t */

/**
 * @typedef   	taskFunc_t
 * @brief    	任务函数类型
 */
typedef void (*taskFunc_t)(void *);

/**
 * @typedef   	taskStack_t
 * @brief    	Cortex-M堆栈单元类型
 * 
 * 堆栈单元大小为32位
 */
typedef uint32_t taskStack_t;

/**
 * @struct		Task_t
 * @brief		任务类型
 *
 * 任务类型，包含了一个任务的所有信息
 */
typedef struct _task
{
	/**  
	 * @var		stack
	 * @brief	task的当前堆栈指针
	 *
	 * 每个任务都有他自己的堆栈，用于在运行过程中存储临时变量等一些环境参数
	 */
	taskStack_t *stack;		
}Task_t;

void taskInit(Task_t *task, taskFunc_t entry, void *param, uint32_t * stack);
void taskSwitch(void);
void taskSched(void);
void taskRunFirst(void);

extern Task_t *currentTask;
extern Task_t *nextTask;
extern Task_t *taskTable[2];
#endif
