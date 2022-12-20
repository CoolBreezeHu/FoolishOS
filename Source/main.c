/**************************************************************************//**
 * @file     main.c
 * @brief    the main function file for project
 *
 * @author   huxing 
 * @date     2022-12-20 09:30:44
 ******************************************************************************/
int g_flag = 0;

void delay(int n)
{
	while(n--);
}	

int main()
{
	for (;;)
	{
		delay(10000);
		g_flag = 1;
		delay(10000);
		g_flag = 0;
	}
}
