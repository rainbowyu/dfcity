#include <Wire.h>

#define Address_Bottom 2        //�ӻ���ַ
#define DEBUG
int Distance[3];//�洢6��ģ��ڲɼ�������ֵ
int Dist_Max=0,Num_Max=0;//�ɼ���������ֵ�е����ֵ�����ֵ���ڵĺ���
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
		Distance[i]=analogRead(i);//������i�ڵ�ģ������ֵ
	}
	for(int i=0;i<3;i++)        //�ҳ����ֵ�������
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
	 if(Dist_Max>100)                            //�������ֵ���ں��뷢����ͬ����
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
	Wire.beginTransmission(Address_Bottom); //�������ݸ���ַΪ2������
	Wire.write(command);        //��������
	Wire.write(num);        //��������
	Wire.endTransmission();    // ֹͣ����
#ifdef DEBUG
	Serial.print("num:");//���ڴ�ӡ������ʱ�õ���
	Serial.println(num);//���ڴ�ӡ������ʱ�õ���
#endif
}
 

