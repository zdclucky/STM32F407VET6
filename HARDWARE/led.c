#include "led.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com							  
////////////////////////////////////////////////////////////////////////////////// 	 

#define GPIO_LED      GPIOA
#define GPIO_PIN_LED0 GPIO_Pin_6
#define GPIO_PIN_LED1 GPIO_Pin_7


//��ʼ��PA6��PA7Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED0 | GPIO_PIN_LED1;//LED0��LED1��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIO_LED, &GPIO_InitStructure);//��ʼ��GPIO
	
  GPIO_SetBits(GPIO_LED,GPIO_PIN_LED0 | GPIO_PIN_LED1);//���øߣ�����
}

void LED_Open(LED led)
{
    switch(led)
    {
    case LED0:
        GPIO_ResetBits(GPIO_LED,GPIO_PIN_LED0);
        break;
    case LED1:
        GPIO_ResetBits(GPIO_LED,GPIO_PIN_LED1);
        break;
    default:
        break;
    }
}
void LED_Close(LED led)
{
    switch(led)
    {
    case LED0:
        GPIO_SetBits(GPIO_LED,GPIO_PIN_LED0);
        break;
    case LED1:
        GPIO_SetBits(GPIO_LED,GPIO_PIN_LED1);
        break;
    default:
        break;
    }
}







