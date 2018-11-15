/* 主程序 */
#include <stdio.h>
#include "Main.h"
#include "ExtToOs.h"

/************************************************
函数名称		： System_Initializes
功    能	： 系统初始化
参    数	： 无
返 回 值		： 无
作    者	： zhaoancai
*************************************************/

void System_Initializes(void)
{
	Stm32_Clock_Init(360,8,4,8);	// 系统时钟90MHZ
	delay_init(90);					// 延时函数初始化
	LED_Initializes();
	Exit_Initializes();				// 外部中断初始化
	FMC_Initializes ();				// FMC初始化
//	TIMER_Initializes();			// 定时器初始化
	USART_Initializes();			// 串口初始化
	IDEP_Initializes();				// 内部总线初始化
}

int main(void)
{
    u32 TimeCnt = 0;
    s8 Error = 0;
    IOData DataStream;
		s8 num = 0;
		s8 i = 0;
	
    // 系统初始化
	System_Initializes();
	
    /* 系统启动 */
    StartUp();

    printf("Start: ...\n");


    while(1)
    {        
        if(TimeCnt % 200000 == 0)
        {
            /* 数据仿真 */
            Error = SimuData(&DataStream);
						for (; num < 23; num++)
						{
							for (i = 0; i < DataStream.DevData[num].Length; i++)
							{
								printf("第%d个设备数据、第%d字节：%d\n", num, i, DataStream.DevData[num].Data[i]);
							}
							
						}
             
            /* 周期性检测 */
    
            /* 数据预处理 */
            DataPre(&DataStream);

    
            /* 故障判断 */
            FaultJudge(&DataStream);

    
            /* 余度管理 */
            ReduHandle(&DataStream);

    
            /* 进数据处理 */
            InDataHandle(&DataStream);

            
            /* 任务调度函数 */
            AppTaskScheduler20ms();
            
            AppTaskSchedulerOther(TimeCnt / 20);


            /* 出数据处理 */
            OutDataHandle(&DataStream);
        }

        
        /* 时标模拟 */
        TimeCnt++;
        if(TimeCnt == 40 * 60 * 60 * 1000)
        {
            TimeCnt = 0;
        }

    }

    return 0;

}




