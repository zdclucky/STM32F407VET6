#include "led.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com							  
////////////////////////////////////////////////////////////////////////////////// 	 

#define GPIO_LED      GPIOA
#define GPIO_PIN_LED0 GPIO_Pin_6
#define GPIO_PIN_LED1 GPIO_Pin_7


//初始化PA6和PA7为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED0 | GPIO_PIN_LED1;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIO_LED, &GPIO_InitStructure);//初始化GPIO
	
  GPIO_SetBits(GPIO_LED,GPIO_PIN_LED0 | GPIO_PIN_LED1);//设置高，灯灭
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







