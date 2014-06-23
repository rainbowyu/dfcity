#include <Wire.h>

#define Address_Bottom 2        //从机地址
#define DEBUG
int Distance[3];//存储6个模拟口采集到的数值
int Dist_Max=0,Num_Max=0;//采集到的六个值中的最大值和最大值所在的号码
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{	
	if (Serial.available())
   {
     if (SernumBefore!=Sernum)
     {
       switch (Sernum)
       {
         case '4':if (SernumBefore==3){Send_Command('S',0);delay(3000);Send_Command('F',150);}break;
         case '5':Send_Command('S',0);delay(8000);Send_Command('F',150);break;
         case '7':if (SernumBefore==6){Send_Command('S',0);delay(3000);Send_Command('F',150);}break;
         default:break;
       }
     }
     SernumBefore=Sernum;
   }
   
	Num_Max=0;
	Dist_Max=0;
	for(int i=0;i<3;i++)
	{
		Distance[i]=analogRead(i);//读出第i口的模拟量的值
	}
	for(int i=0;i<3;i++)        //找出最大值及其号码
	{
		if(Distance[i]>Dist_Max)
		{
			Dist_Max=Distance[i];
			Num_Max=i;
		}  
#ifdef DEBUG
		Serial.print(Distance[i]);
		Serial.print(" ");
#endif
	}
#ifdef DEBUG
	Serial.print("Dist_Max:");
	Serial.println(Dist_Max);
	Serial.print("Num_Max:");
	Serial.println(Num_Max);
#endif
	 if(Dist_Max>100)                            //根据最大值所在号码发出不同命令
	 {
		switch (Num_Max)
		{
			case 0:Send_Command('L',150);break;
			case 1:Send_Command('F',150);break;
			case 2:Send_Command('R',150);break;
		}
	 }
}

void Send_Command(char command,int num)
{
	Wire.beginTransmission(Address_Bottom); //发送数据给地址为2的器件
	Wire.write(command);        //发送数据
	Wire.write(num);        //发送数据
	Wire.endTransmission();    // 停止发送
#ifdef DEBUG
	Serial.print("num:");//串口打印，调试时用到的
	Serial.println(num);//串口打印，调试时用到的
#endif
}
 

