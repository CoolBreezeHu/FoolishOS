/**************************************************************************//**
 * @file     	public.h
 * @brief    	公用头文件
 *
 * @author   	huxing
 * @version  	V0.0.4
 * @date     	2022-11-4 15:51:34
 ******************************************************************************/
#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#define NVIC_INT_CTRL		0xE000ED04		/*!< 中断控制及状态寄存器 */
#define NVIC_PENDSVSET		0x10000000		/*!< 触发软件中断的值 */
#define NVIC_SYSPRI2		0xE000ED22		/*!< 系统优先级寄存器 */
#define NVIC_PENDSV_PRI		0x000000FF		/*!< 配置优先级的值 */

/**
 * @def 		MEM8(addr)
 * @param 		addr 待转换的地址
 * @return 		unsigned char * 指针
 */
#define MEM8(addr)			*(volatile unsigned char *)(addr)
	
/**
 * @param 		addr 待转换的地址
 * @return 		unsigned long * 指针
 */
#define MEM32(addr)			*(volatile unsigned long *)(addr)

#endif
