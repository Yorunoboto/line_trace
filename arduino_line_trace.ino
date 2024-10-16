#define R_PWM_0 5
#define R_PWM_1 3
#define L_PWM_0 6
#define L_PWM_1 9
#define OUT1 A0
#define OUT2 A1
#define OUT3 A2
#define OUT4 A3
#define OUT5 A4
#define OUT6 A5
#define OUT7 A6
#define OUT8 A7
#define STBY 4

int SensorValue[]={OUT1,OUT2,OUT3,OUT4,OUT5,OUT6,OUT7,OUT8};
int value = 0;


//左右モータを前進させる
void moveForward(int l,int r){
  int speedchange_r = 0;
  int speedchange_l = 0;
  r *= 0.95;
  speedchange_r = map(r,0,255,45,60);
  speedchange_l = map(l,0,255,45,60);
  r *= 0.31;
  l *= 0.31;

  analogWrite(R_PWM_0,r);
  digitalWrite(R_PWM_1,LOW);
  analogWrite(L_PWM_0,l);
  digitalWrite(L_PWM_1,LOW);

  Serial.print("R:");
  Serial.print(r);
  Serial.print(" L:");
  Serial.println(l);

}

void setup() {
  Serial.begin(9600);
  pinMode(R_PWM_0,OUTPUT);
  pinMode(R_PWM_1,OUTPUT);
  pinMode(L_PWM_0,OUTPUT);
  pinMode(L_PWM_1,OUTPUT);
  digitalWrite(STBY,1);
}

void loop() {
  int buf =0;
  delay(100);
  // センサの値を取得する
  for(int i = 0; i < 8; i++){
    value = analogRead(SensorValue[i]);
    value = map(value,0,1023,0,255);
    Serial.print(value);
    Serial.print(' ');
    if(value >= 150){
      buf |= 1 << i;
    }
  }
  Serial.print(buf);
  Serial.print(' ');
  // モータを前進させる
  switch(buf){
    case 0b10000000:moveForward(255,31);
      break;
    case 0b11000000:moveForward(255,62);
      break;
    case 0b01000000:moveForward(255,93);
      break;
    case 0b01100000:moveForward(255,124);
      break;
    case 0b00100000:moveForward(255,155);
      break;
    case 0b00110000:moveForward(255,186);
      break;
    case 0b00010000:moveForward(255,217);
      break;
    case 0b00011000:moveForward(255,255);
      break;
    case 0b00001000:moveForward(217,255);
      break;
    case 0b00001100:moveForward(186,255);
      break;
    case 0b00000100:moveForward(155,255);
      break;
    case 0b00000110:moveForward(124,255);
      break;
    case 0b00000010:moveForward(93,255);
      break;
    case 0b00000011:moveForward(62,255);
      break;
    case 0b00000001:moveForward(31,255);
      break;
      
    default:moveForward(0,0);
  }
  Serial.println(' ');
  digitalWrite(STBY,0);
  delay(1);
  digitalWrite(STBY,1);  
}

  
