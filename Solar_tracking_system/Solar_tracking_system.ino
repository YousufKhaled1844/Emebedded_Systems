// Embeddedproject_PID
#include <MCP3008.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>


#define LDR_1 A0
#define LDR_2 A1
#define LDR_3 A2
#define LDR_4 A3
//define pin connections
#define CS_PIN 3
#define CLOCK_PIN 13
#define MOSI_PIN 11
#define MISO_PIN 12


#define RECV_PIN 2
// base motor  
#define base_motor_speed 10
#define base_motor_clockwise 5
#define base_motor_Anti_clockwise 4

// PV cell rotor
#define pv_motor_speed  9
#define pv_motor_clockwise 7
#define pv_motor_Anti_clockwise 6

void base_clockwise();
void base_Anti_clockwise();
void pv_clockwise();
void pv_Anti_clockwise();
void Stop_pv();
void Stop_base();
void Error();
void Move();
void PID_control();
void track();
void Display();
void manual();
void State (int X );

MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
IRrecv irrecv(RECV_PIN);

float Error_arr[2]={0};
float e_1,e_2,u_1,up_1,ud_1,e_old_1,u_2,up_2,ud_2,e_old_2; //e1 Horizontal // e2 vertical

// With large Kp and large  Ki ss_error=0 and ossilate with kd
float Kp_1=0.6; 
float Kd_1=0.7;

float Kp_2=0.8;
float Kd_2=0.5;

int Speed = 50 ; 

int flag=0;

void setup()
{
  pinMode(base_motor_speed,OUTPUT);
  pinMode(base_motor_clockwise,OUTPUT);
  pinMode(base_motor_Anti_clockwise,OUTPUT);
  pinMode(pv_motor_speed ,OUTPUT);
  pinMode(pv_motor_clockwise,OUTPUT);
  pinMode(pv_motor_Anti_clockwise,OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear(); 
  irrecv.enableIRIn();
}

void loop() 
{
 if (irrecv.decode())
    {  
      
      if (irrecv.decodedIRData.decodedRawData == 0xB847FF00)
      {
       if(flag == 0 || flag==2)
       {
          flag = 1;
        }else if(flag ==1)
        {
          flag = 2;
        }
       }
      }
      // Receive the next value
       irrecv.resume();   
    

    if(flag == 0)
    {
      State(10);
     }else if(flag == 1)
     {
         State(7);
         delay(1000);
         track(); 
         Display();
     }else if(flag == 2)
     {
         State(6);
         manual();
      }
    
}
void Error(void)
{
 Error_arr[0]=analogRead(LDR_1)-analogRead(LDR_3);  // Horizontal LDRs
 Error_arr[1]=analogRead(LDR_2)-analogRead(LDR_4);  // Vertical
  
} 

 void base_clockwise () 

{
        analogWrite (base_motor_speed,  Speed);
        digitalWrite(base_motor_clockwise, HIGH);
        digitalWrite(base_motor_Anti_clockwise,LOW);
}

void base_Anti_clockwise () 

{
        analogWrite (base_motor_speed,  Speed);
        digitalWrite(base_motor_clockwise, LOW);
        digitalWrite(base_motor_Anti_clockwise,HIGH);
}

  void pv_clockwise () 

{
        analogWrite (pv_motor_speed,  Speed);
        digitalWrite(pv_motor_clockwise, HIGH);
        digitalWrite(pv_motor_Anti_clockwise,LOW);
}

void pv_Anti_clockwise () 

{
        analogWrite (pv_motor_speed,  Speed);
        digitalWrite(pv_motor_clockwise, LOW);
        digitalWrite(pv_motor_Anti_clockwise,HIGH);
}

void Stop_pv(){
  
       digitalWrite(pv_motor_clockwise,LOW);
       digitalWrite(pv_motor_Anti_clockwise,LOW);
    
}

void Stop_base(){
  
       digitalWrite(base_motor_clockwise,LOW); 
       digitalWrite(base_motor_Anti_clockwise,LOW);
  
}


void PID_control ()
{
  Error();
  e_1 = Error_arr[0];
  e_2 = Error_arr[1];

  up_1=Kp_1*e_1;
  ud_1=Kd_1*(e_1-e_old_1);
  u_1=up_1+ud_1;
  e_old_1=e_1; 

  up_2=Kp_2*e_2;
  ud_2=Kd_2*(e_2-e_old_2);
  u_2=up_2+ud_2;
  e_old_2=e_2; 
}
  
void track()
{
   PID_control ();

  if(u_1>0 && abs(u_1)>25)
  {
    Speed=abs(u_1);  
    pv_clockwise () ;
    Serial.println("up");
  }else if(u_1<0 && abs(u_1)>25)
  {
    Speed=abs(u_1);
    pv_Anti_clockwise () ;
    Serial.println("down");
  }else if(abs(u_1)<25)
  {
    Stop_pv();
    }
  
    if(u_2>0 && abs(u_2)>25)
  {
    Speed=abs(u_2);
    base_clockwise () ;
    Serial.println("right");
  }else if(u_2<0 && abs(u_2)>25)
  {
    Speed=abs(u_2);
    base_Anti_clockwise ();
    Serial.println("Left");
  }else if(abs(u_2)<25)
  {
     Stop_base();
  }
  
  }
  void Display()
  {
    Serial.println("ll");
   float voltage = ((float)(adc.readADC(4)*2*5)/1023)+2;
   lcd.setCursor(0, 0);
   lcd.print("Voltage :");
   lcd.setCursor(11,0);
   lcd.print((float)voltage,5);
    }
  void manual()
  {
     if (irrecv.decodedIRData.decodedRawData == 0xE718FF00)
     {
       pv_clockwise () ;
       State (1);
     }
     else if (irrecv.decodedIRData.decodedRawData == 0xAD52FF00){
        pv_Anti_clockwise () ;
        State (2);
      }

      else if (irrecv.decodedIRData.decodedRawData == 0xA55AFF00){
      base_clockwise () ;
      State (3);

      }else if (irrecv.decodedIRData.decodedRawData == 0xF708FF00)
      {
      base_Anti_clockwise () ;
       State (4);
      }else if (irrecv.decodedIRData.decodedRawData == 0xE31CFF00)   
      {
        Stop_base();
        Stop_pv();
        State(5);
  
      }

      else if (irrecv.decodedIRData.decodedRawData == 0xBA45FF00){
        Speed = 80 ;  
      }else if(irrecv.decodedIRData.decodedRawData ==0xB946FF00)
      {
        Speed = 120 ;  
        }
    }

    void State (int X )
{
  lcd.clear();
  lcd.setCursor(0, 0);
  switch(X) {
  case 1:
   lcd.print("moveUp");
   break;
 
    case 2:
    lcd.print("movedown");
    break;
    case 3:
    lcd.print("moveright");
    break;
    case 4:
    lcd.print("moveleft");
    break;
    case 5:
    lcd.print("stop moving ");
    break;
    case 6:
    lcd.print("Manual mode ");
    break;
    case 7:
    lcd.print("Automatic mode ");
    break;
    default:
    lcd.print("waiting");
}
}
