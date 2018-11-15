/* ������ */
#include <stdio.h>
#include "Main.h"
#include "ExtToOs.h"

/************************************************
��������		�� System_Initializes
��    ��	�� ϵͳ��ʼ��
��    ��	�� ��
�� �� ֵ		�� ��
��    ��	�� zhaoancai
*************************************************/

void System_Initializes(void)
{
	Stm32_Clock_Init(360,8,4,8);	// ϵͳʱ��90MHZ
	delay_init(90);					// ��ʱ������ʼ��
	LED_Initializes();
	Exit_Initializes();				// �ⲿ�жϳ�ʼ��
	FMC_Initializes ();				// FMC��ʼ��
//	TIMER_Initializes();			// ��ʱ����ʼ��
	USART_Initializes();			// ���ڳ�ʼ��
	IDEP_Initializes();				// �ڲ����߳�ʼ��
}

int main(void)
{
    u32 TimeCnt = 0;
    s8 Error = 0;
    IOData DataStream;
		s8 num = 0;
		s8 i = 0;
	
    // ϵͳ��ʼ��
	System_Initializes();
	
    /* ϵͳ���� */
    StartUp();

    printf("Start: ...\n");


    while(1)
    {        
        if(TimeCnt % 200000 == 0)
        {
            /* ���ݷ��� */
            Error = SimuData(&DataStream);
						for (; num < 23; num++)
						{
							for (i = 0; i < DataStream.DevData[num].Length; i++)
							{
								printf("��%d���豸���ݡ���%d�ֽڣ�%d\n", num, i, DataStream.DevData[num].Data[i]);
							}
							
						}
             
            /* �����Լ�� */
    
            /* ����Ԥ���� */
            DataPre(&DataStream);

    
            /* �����ж� */
            FaultJudge(&DataStream);

    
            /* ��ȹ��� */
            ReduHandle(&DataStream);

    
            /* �����ݴ��� */
            InDataHandle(&DataStream);

            
            /* ������Ⱥ��� */
            AppTaskScheduler20ms();
            
            AppTaskSchedulerOther(TimeCnt / 20);


            /* �����ݴ��� */
            OutDataHandle(&DataStream);
        }

        
        /* ʱ��ģ�� */
        TimeCnt++;
        if(TimeCnt == 40 * 60 * 60 * 1000)
        {
            TimeCnt = 0;
        }

    }

    return 0;

}




