/**************************************************************************//**
 * @file     main.c
 * @brief    the main function file for project
 *
 * @author   huxing 
 * @date     2022-12-20 09:30:44
 ******************************************************************************/
#include "FoolishOS.h"

void delay(int n);

Task_t task1;
Task_t task2;
taskStack_t env1[1024];
taskStack_t env2[1024];

int task1Flag;
void task1Entry(void *param)
{
	for (;;) {
		task1Flag = 1;
		delay(100);
		task1Flag = 0;
		delay(100);
		
		taskSched();
	}
}

int task2Flag;
void task2Entry(void *param)
{
	for (;;) {
		task2Flag = 1;
		delay(100);
		task2Flag = 0;
		delay(100);
		
		taskSched();
	}
}

int main()
{
    taskTable[0] = &task1;
	taskTable[1] = &task2;
	nextTask = taskTable[0];
	
	taskInit(&task1, task1Entry, (void *)111, &env1[1024]);
    taskInit(&task2, task2Entry, (void *)222, &env2[1024]);
	
	taskRunFirst();
	return 0;
}

void delay(int n)
{
	while(n--);
}
