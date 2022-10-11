#include <Servo.h> // Servo library 
// 180 가로(좌/우)모터 최대 범위값
Servo horizontal;           // 가로(좌/우)모터
int servoMhStand= 90;       //  가로(좌/우) 판넬(서보모터) stand value 초기값.
int servoMhLimitHigh = 180; //  가로(좌/우) 최대값
int servoMhLimitLow = 0;    //  가로(좌/우) 최저값

// 65 세로(상/하)모터 최대 범위값 
Servo vertical;             // 세로(상/하)모터
int servoMvStand= 90;       //  세로(상/하) 판넬(서보모터) stand value 초기값.
int servoMvLimitHigh = 150; //세로(상/하) 최대값
int servoMvLimitLow = 15;   //세로(상/하) 최저값 


int ldrrt = 0; //LDR - BOTTOM RIGHT 
int ldrlt = 1; //LDR - BOTTOM LEFT   
int ldrrd = 2; //LDR - TOP RIGHT
int ldrld = 3; //LDR - TOP LEFT
  
int delay_time = 2;
int tol_val = 7;

void setup()
{
  Serial.begin(9600);

// 서보모터 연결
    horizontal.attach(9); //가로
    vertical.attach(10);  //세로
    
    




//  horizontal.write(90); // 가로(좌/우) 판넬(서보모터) stand.
//  vertical.write(45);   // tpfh(상/하) 판넬(서보모터) stand.

    
}

void loop() 
{
  // Ldr 값을 Read.
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
 
  Serial.print("lt:");
  Serial.print(lt);
  Serial.print("rt:");
  Serial.print(rt);
  Serial.print("ld:");
  Serial.print(ld);
  Serial.print("rd:");
  Serial.print(rd);
  
  int avt = (lt + rt) / 2; // 평균값 top
  int avd = (ld + rd) / 2; // 평균값 down
  int avl = (lt + ld) / 2; // 평균값 left
  int avr = (rt + rd) / 2; // 평균값 right

  int dvert = avt - avd; // 상하 차이 값 계산
  int dhoriz = avl - avr;// 좌우 차이 값 계산
  Serial.print("delay_time:");
  Serial.print(delay_time);
  Serial.print(" ");
  Serial.print("tol_val:"); 
  Serial.print(tol_val);
  Serial.print(" ");
  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(delay_time);
  Serial.print("   ");
  Serial.print(tol_val);
  Serial.println(" ");
  
    
  if (-1*tol_val > dvert || dvert > tol_val)
  {
    if (avt > avd)
   {
      servoMvStand= ++servoMvStand;
      if (servoMvStand> servoMvLimitHigh) 
      { 
       servoMvStand= servoMvLimitHigh;
      }
    }
   else if (avt < avd)
   {
      servoMvStand= --servoMvStand;
      if (servoMvStand< servoMvLimitLow)
    {
      servoMvStand= servoMvLimitLow;
    }
   }
  vertical.write(servoMvStand);
  }
  
  if (-1*tol_val > dhoriz || dhoriz > tol_val) 
  {
    if (avl > avr)
    {
      servoMhStand= --servoMhStand;
     if (servoMhStand< servoMhLimitLow)
      {
     servoMhStand= servoMhLimitLow;
     }
   }
    else if (avl < avr)
   {
     servoMhStand= ++servoMhStand;
      if (servoMhStand> servoMhLimitHigh)
      {
       servoMhStand= servoMhLimitHigh;
      }
   }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoMhStand);
  }
   delay(delay_time);

}
