#include "reg51.h"
#include "intrins.h"

#define LEDP2 P2 //p2端口
#define LEDP0 P0 //p0端口

typedef unsigned char u8;
typedef unsigned int u16; 

u8 code LedDuan[] = {
0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c,
0x39, 0x5e, 0x79, 0x71
};

// 延时函数 约1us
void Delay(u16 timer)
{
	 while(timer--);
}

//LED
sbit Led0 = P2^0;
sbit Led1 = P2^1;
sbit Led2 = P2^2;
sbit Led3 = P2^3;
sbit Led4 = P2^4;
sbit Led5 = P2^5;
sbit Led6 = P2^6;
sbit Led7 = P2^7;

//Buzz
sbit Buzz = P1^5;

//key
sbit KEY1 = P3^1;


//38译码器
sbit InA = P2^2;
sbit InB = P2^3;
sbit InC = P2^4;



//流水灯
void LedLiuShui()
{
	u8 i = 0;
	LEDP2 = 0xfe;
	Delay(50000);
	while(1){
		for(i = 0; i < 7; i++){
			LEDP2 = _crol_(LEDP2, 1);
			Delay(50000);
		}
		
		for(i = 0; i < 7; i++){
			LEDP2 = _cror_(LEDP2, 1);
			Delay(50000);
		}
	}
}

//led闪烁
void LedLitOne()
{
	while(1){
	 	Led0 = 0;
		Delay(500000);
		Led0 = 1;
		Delay(500000);
	}
}

//蜂鸣器
void BuzzOn()
{
	u16 i = 0;
	while(1){
		for(i = 0; i < 500; i++){
			Buzz = ~Buzz;	
			Delay(10);	
		}
		Delay(50000);
		Delay(50000);
	}	
}

//数码管
void LedLight()
{
	InA = 0;
	InB = 0;
	InC = 0;
	LEDP0 = LedDuan[6];
	while(1){

	}	

}

//数码管流水
void BLedLiuShui()
{
	u8 i = 0;
	while(1){
		 for(i = 0; i < 8; i++){
		 	switch(i){			
				case (0):
					InA = 0;
					InB = 0;
					InC = 0;
					LEDP0 = LedDuan[0];
					break;
				case (1):
					InA = 1;
					InB = 0;
					InC = 0;
					LEDP0 = LedDuan[1];
					break;	
				case (2):
					InA = 0;
					InB = 1;
					InC = 0;
					LEDP0 = LedDuan[2];
					break;
				case (3):
					InA = 1;
					InB = 1;
					InC = 0;
					LEDP0 = LedDuan[3];
					break;
				case (4):
					InA = 0;
					InB = 0;
					InC = 1;
					LEDP0 = LedDuan[4];
					break;
				case (5):
					InA = 1;
					InB = 0;
					InC = 1;
					LEDP0 = LedDuan[5];
					break;	
				case (6):
					InA = 0;
					InB = 1;
					InC = 1;
					LEDP0 = LedDuan[6];
					break;
				case (7):
					InA = 1;
					InB = 1;
					InC = 1;
					LEDP0 = LedDuan[7];
					break;
		 	}
		   	Delay(100);
		 	P0 = 0x00;
		 }
		 			
		 	
	}
	

}

//独立按键
void DuLiAnJian()
{
	while(1){
		if (KEY1 == 0){
			Delay(10000);
			if (KEY1 == 0){
				Led0 = ~Led0;	
			}
			while(!KEY1);
			Delay(10000);
		}
	}

}

//矩阵按键
void JuZhenAnJian()
{
	u8 count = 0;
	u8 keyValuer = 0;
	InA = 0;
	InB = 0;
	InC = 0;
	while(1){
		P1 = 0x0f;
		if(P1 != 0x0f){
			Delay(10000);
			P1 = 0x0f;
			if(P1 != 0x0f){
				switch(P1){
					case(0x07):
						keyValuer = 0;
						break;
					case(0x0d):
						keyValuer = 1;
						break;
					case(0x0b):
						keyValuer = 2;
						break;
					case(0x0e):
						keyValuer = 3;
						break;
				}
				P1 = 0xf0;
				switch(P1){
					case(0xe0):
						keyValuer = keyValuer;
						break;
					case(0xb0):
						keyValuer = keyValuer + 4;
						break;
					case(0xd0):
						keyValuer = keyValuer + 8;
						break;
					case(0x70):
						keyValuer = keyValuer + 12;	
						break;
				}
				LEDP0 = LedDuan[keyValuer];
				while((count < 50) && (P1 != 0xf0)){
					Delay(10000);
					count++;
				}
			}
		}
		
	}
}

void main()
{
	JuZhenAnJian();
}



