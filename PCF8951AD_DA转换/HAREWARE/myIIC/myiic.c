#include "myiic.h"
#include "delay.h"
//³õÊ¼»¯IIC
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);
}


//²úÉúIICÆðÊ¼ÐÅºÅ
void IIC_Start(void)
{
	SDA_OUT();//sdaÏßÊä³ö
	IIC_SDA=1;
	IIC_SCL=1;
	delay_us(4);
	IIC_SDA=0;//START:when CLK is high,DATA change from to low
	delay_us(4);
	IIC_SCL=0;//Ç¯×¡IIC×ÜÏß£¬×¼±¸·¢ËÍ»ò½ÓÊÕÊý¾Ý
}

//²úÉúIICÍ£Ö¹ÐÅºÅ
void IIC_Stop(void)
{
	SDA_OUT();//sdaÏßÊä³ö
	IIC_SCL=0;
	IIC_SDA=0;//STOP :when CLK is hieh DATA change from low to high
	delay_us(4);
	IIC_SCL=1;
	IIC_SDA=1;//·¢ËÍIIC×ÜÏß½áÊøÐÅºÅ
	delay_us(4);	
}

//µÈ´ýÓ¦´ðÐÅºÅµ½À
//·µ»ØÖµ£º1£¬½ÓÊÕÓ¦´ðÊ§°Ü
//·µ»ØÖµ£º0 ½ÓÊÕÓ¦´ð³É¹¦
u8 IIC_Wait_Ack(void)
{
	u8 ucErrtime=0;
	SDA_IN();//SDAÉèÖÃÊäÈë
  IIC_SDA=1;delay_us(1);
	IIC_SCL=4;delay_us(1);
	while(READ_SDA)
	{
		ucErrtime++;
		if(ucErrtime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//Ê±ÖÓÊä³ö0
	return 0;
}

//²úÉúÓ¦´ðÐÅºÅ
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;	
}
//²»²úÉúACKÓ¦´ð
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//IIC·¢ËÍÒ»¸ö×Ö½Ú
//·µ»Ø´Ó»úÓÐÎÞÓ¦´ð
//1£ºÓÐÓ¦´ð
//0£ºÎåÓ¦´ð
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	SDA_OUT();
	IIC_SCL=0;//À­µÍÊ±ÖÓ¿ªÊ¼Êý¾Ý´«Êä
	for(t=0;t<8;t++)
	{
		if((txd&0x80)>>7)
		IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1;
		delay_us(2);//¶ÔTEA5767ÕâÉ½¸èÑÓÊ±¶¼ÊÇ±ØÐëµÄ
		IIC_SCL=1;
		delay_us(2);
		IIC_SCL=0;
		delay_us(2);
			
	}
}
//¶Á1¸ö×Ö½Ú£¬ack=1Ê±£¬·¢ËÍACK£¬ack=0£¬·¢ËÍnACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDAÉèÖÃÎªÊäÈë
	for(i=0;i<8;i++)
	{
		IIC_SCL=0;
		delay_us(2);
		IIC_SCL=1;
		receive<<=1;
		if(READ_SDA)receive++;
		delay_us(1);
	}
	if(!ack)     //ack=0
		IIC_NAck();//·¢ËÍnAck
	else         //ack=1
		IIC_Ack();//·¢ËÍACK
	return receive; 
}	
 



                         
                    
