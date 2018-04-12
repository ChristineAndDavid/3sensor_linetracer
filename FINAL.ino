//code is
int count=0;
int A_1A = 6;
int A_1B = 11;
int B_1A = 9;
int B_1B = 5;
int leftLineSensor = 12;
int rightLineSensor = 3;
int midLineSensor = 8;

int trigPin = 13;
int echoPin = 2;
bool wave_finished =true;
unsigned long _start, _end;
float distance = 0;

#define speed 255
volatile int isObstacle=0;
int l1=1;
int l2=1;
int l3=1;

int f1[2]={0};
int f2[2]={0};
int f3[2]={0};

void Out_Wave(){
  wave_finished = false;

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
}

void ISR_echo(){
  switch(digitalRead(echoPin)){
    case HIGH:
    _start = micros();
    break;
    case LOW:
    _end = micros();
    wave_finished = true;
    break;
  }
}
//////////////////////////////////////

void setup()
{

 pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);
  attachInterrupt(0, ISR_echo ,CHANGE);

  Out_Wave();
  
  pinMode(leftLineSensor, INPUT);
  pinMode(rightLineSensor, INPUT);
  pinMode(midLineSensor, INPUT);
}
///////////////////////////////////////////////////

void loop()
{
  if(wave_finished){
    distance = (_end - _start)*0.034/2;
    Out_Wave();
  }
  
  if (distance < 20) {
  analogWrite(A_1A, speed);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, speed);
  delay(500);
  }
  else{  
    l1=!digitalRead(leftLineSensor);
    l2=!digitalRead(midLineSensor);
    l3=!digitalRead(rightLineSensor);
/////////////////////////////////////////////////////////////////////
if(l1==1&&l2==1&&l3==1)   //feedback when comes all sensor on white
{
l1=f1[1];
l2=f2[1];
l3=f3[1];
}
if(l1==1&&l2==1&&l3==1)   //feedback when comes all sensor on white
{
l1=f1[0];
l2=f2[0];
l3=f3[0];
}
////////////////////////////////////////////////////////////////////////////
if(l1==0&&l3==1)   //left turn
{
  if(l2){
  analogWrite(A_1A, speed-50);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
  }
  else{
    analogWrite(A_1A, speed-50);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, speed/2);
  analogWrite(B_1B, 0);
  }
}
else if(l1==1&&l3==0)  //right turn
{
  if(l2){
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, speed-50);
  analogWrite(B_1B, 0);
  }
  else{
    analogWrite(A_1A, speed/2);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, speed-50);
  analogWrite(B_1B, 0);
  }
}
else if(l1==1&&l2==0&&l3==1)  //go forward straight
{
  analogWrite(A_1A, speed);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, speed);
  analogWrite(B_1B, 0);
}
else if(l1==0&&l2==0&&l3==0) //stop
{
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}



///////////////////////////////////////////////////////////////////
f1[0]=f1[1]; f1[1]=l1;
f2[0]=f2[1]; f2[1]=l2;
f3[0]=f3[1]; f3[1]=l3;       //memory variables
count=count+1;
////////////////////////////////////////////////////////////////////
  }
} 
