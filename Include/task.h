/**************************************************************************//**
 * @file     	task.h
 * @brief    	����ͷ�ļ�
 *
 * @author   	huxing
 * @version  	V0.0.4
 * @date     	2022-11-4 15:51:45
 ******************************************************************************/
#ifndef __TASK_H_
#define __TASK_H_

#include <stdint.h>	 /*!< ��׼ͷ�ļ�����������˳��õ����Ͷ��壬�磺uint32_t */

/**
 * @typedef   	taskFunc_t
 * @brief    	����������
 */
typedef void (*taskFunc_t)(void *);

/**
 * @typedef   	taskStack_t
 * @brief    	Cortex-M��ջ��Ԫ����
 * 
 * ��ջ��Ԫ��СΪ32λ
 */
typedef uint32_t taskStack_t;

/**
 * @struct		Task_t
 * @brief		��������
 *
 * �������ͣ�������һ�������������Ϣ
 */
typedef struct _task
{
	/**  
	 * @var		stack
	 * @brief	task�ĵ�ǰ��ջָ��
	 *
	 * ÿ�����������Լ��Ķ�ջ�����������й����д洢��ʱ������һЩ��������
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
