/**************************************************************************//**
 * @file     	public.h
 * @brief    	����ͷ�ļ�
 *
 * @author   	huxing
 * @version  	V0.0.4
 * @date     	2022-11-4 15:51:34
 ******************************************************************************/
#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#define NVIC_INT_CTRL		0xE000ED04		/*!< �жϿ��Ƽ�״̬�Ĵ��� */
#define NVIC_PENDSVSET		0x10000000		/*!< ��������жϵ�ֵ */
#define NVIC_SYSPRI2		0xE000ED22		/*!< ϵͳ���ȼ��Ĵ��� */
#define NVIC_PENDSV_PRI		0x000000FF		/*!< �������ȼ���ֵ */

/**
 * @def 		MEM8(addr)
 * @param 		addr ��ת���ĵ�ַ
 * @return 		unsigned char * ָ��
 */
#define MEM8(addr)			*(volatile unsigned char *)(addr)
	
/**
 * @param 		addr ��ת���ĵ�ַ
 * @return 		unsigned long * ָ��
 */
#define MEM32(addr)			*(volatile unsigned long *)(addr)

#endif
