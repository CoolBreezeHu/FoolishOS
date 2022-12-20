/**************************************************************************//**
 * @file     main.c
 * @brief    the main function file for project
 *
 * @author   huxing 
 * @date     2022-12-20 09:30:44
 ******************************************************************************/
#define NVIC_INT_CTRL       0xE000ED04      /*!< int ctrl1 */
#define NVIC_PENDSVSET      0x10000000      /*!< int ctrl2 */
#define NVIC_SYSPRI2        0xE000ED22      /*!< int ctrl3 */
#define NVIC_PENDSV_PRI     0x000000FF      /*!< int ctrl4 */

#define MEM8(addr)          *(volatile unsigned char *)(addr)
#define MEM32(addr)         *(volatile unsigned long *)(addr)    

typedef struct _block
{
    unsigned long * stackPtr;
}BlockType_t;

void triggerPendSVC(void);
void delay(int n);

int g_flag = 0;
BlockType_t *blockPtr;	
BlockType_t block;
unsigned long stackBuff[1024];

int main()
{
    blockPtr = &block;
	for (;;)
	{
		delay(10000);
		g_flag = 1;
		delay(10000);
		g_flag = 0;
        block.stackPtr = &stackBuff[1024];
		triggerPendSVC();
	}
}

void delay(int n)
{
	while(n--);
}

void triggerPendSVC(void)
{
    MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
    MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;   
}

__asm void PendSV_Handler ()
{
    IMPORT blockPtr

    LDR		R0, =blockPtr
    LDR		R0, [R0]
    LDR		R0, [R0]

    // stackBuff[1023]: R11
    // stackBuff[1022]: R10
    // stackBuff[1021]: R9
    // stackBuff[1020]: R8
    // stackBuff[1019]: R7
    // stackBuff[1018]: R6
    // stackBuff[1017]: R5
    // stackBuff[1016]: R4
    STMDB	R0!, {R4-R11}

    LDR		R1, =blockPtr
    LDR		R1, [R1]
    LDR		R0, [R1]

    ADD		R4, R4, #1
    ADD		R5, R5, #1

    LDMIA	R0!, {R4-R11}

    BX		LR
}

