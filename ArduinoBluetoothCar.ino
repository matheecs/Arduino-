int EN1 = 6;  //使能引脚
int EN2 = 5;  
int IN1 = 7;//驱动引脚
int IN2 = 4; 
char receive='t';//默认开始启动时停止
int mode_flag=0;//默认手机控制
   
  
  
void Motor1(int pwm, boolean reverse)//电机1的PWM调速
{
  analogWrite(EN1,pwm);
  if(reverse)
  { 
    digitalWrite(IN1,HIGH);    
  }
  else
  {
    digitalWrite(IN1,LOW);    
  }
}  
          
void Motor2(int pwm, boolean reverse)//电机2的PWM调速
{
  analogWrite(EN2,pwm);
  if(reverse)
  { 
    digitalWrite(IN2,HIGH);    
  }
  else
  {
    digitalWrite(IN2,LOW);    
  }
}
/////////////
void turnleft()//电机左转
{
  Motor1(0,true);
  Motor2(140,true);
}
 
void turnleft_fast()//电机快速左转弯
{
  Motor1(0,true);
  Motor2(200,true);
}
/////////////////
void turnright()//电机右转
{
  Motor1(140,false);
  Motor2(0,false);
}
 
void turnright_fast()//电机快速右转
{
  Motor1(200,false);
  Motor2(0,false);
}
////////////////////// 
void forward()    //直行
{
  Motor1(160,false);
  Motor2(160,true);
}
 
void forward_fast()//快速直行
{
  Motor1(200,false);
  Motor2(200,true);
}
/////////////////////////
 
void back()//后退
{
  Motor1(120,true);
  Motor2(120,false);
}
 
void back_fast()//快速后退
{
  Motor1(200,true);
  Motor2(200,false);
}
//////////////////
void stop()//停止
{
  Motor1(0,false);
  Motor2(0,false);
}                
         
void setup() //初始化输出引脚和蓝牙的串口通信频率
{ 
    int i;
    for(i=4;i<=7;i++) 
      pinMode(i, OUTPUT); 
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    Serial.begin(9600);   
} 
 
 
 
void loop() 
{
  //if((digitalRead(8)==1)&&(digitalRead(9)==0)&&(digitalRead(10)==1))
  //  forward();
  //if((digitalRead(8)==0)&&(digitalRead(9)==1)&&(digitalRead(10)==1))
  //  turnleft();
  //if((digitalRead(8)==1)&&(digitalRead(9)==1)&&(digitalRead(10)==0))
  // turnright(); 
  //if((digitalRead(8)==1)&&(digitalRead(9)==1)&&(digitalRead(10)==1))
  //  stop();
  while(Serial.available()>0)//实时检测串口数据
  {
          receive=Serial.read();
          if(receive=='f')
          {
                   mode_flag=0;
                   receive='t';
          }
          if(receive=='l')
          {
                  mode_flag=1;
          }
  }
 
  switch (mode_flag) //手机蓝牙操控模式
  {
      case 0:switch (receive) 
      {
          case 'w':forward_fast();
            break;
          case 's':back_fast();
            break;
          case 'q':turnleft();
                  break;
          case 'e':turnright();
                  break;
          case 't':stop();
                  break;
          default:break;
      }
        break;
      case 1:switch(PINB&0x07)//自主寻迹模式
          {
            case 0x05:forward();
                    delay(10);break;
            case 0x06:turnleft();
                    delay(10);break;
            case 0x03:turnright();
                    delay(10);break;
            case 0x07:back();
                    delay(10);break;
            default:break;
          }
        break;
      default:break;
  }
}
