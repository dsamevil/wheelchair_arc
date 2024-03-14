#define VRX_PIN  A1
#define VRY_PIN  A2

#define LEFT_THRESHOLD  505
#define RIGHT_THRESHOLD 509
#define UP_THRESHOLD    497
#define DOWN_THRESHOLD  500

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

#define RPWM1 5
#define LPWM1 6
#define REN1  8
#define LEN1  9

#define RPWM2 10
#define LPWM2 11
#define REN2  13
#define LEN2  12

int xValue = 0;
int yValue = 0;
int command = COMMAND_NO;
int max=100,m;
void setup() {
  Serial.begin(9600);
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(LEN1, OUTPUT);
  pinMode(REN1, OUTPUT);
  digitalWrite(REN1, HIGH);
  digitalWrite(LEN1, HIGH);

  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
  pinMode(LEN2, OUTPUT);
  pinMode(REN2, OUTPUT);
  digitalWrite(REN2, HIGH);
  digitalWrite(LEN2, HIGH);
}

void loop() {
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  command = COMMAND_NO;

  if (xValue < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  if (xValue > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  if (yValue < UP_THRESHOLD)
    command = command | COMMAND_UP;
  if (yValue > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;

  
  if (command & COMMAND_UP) {
    Serial.println("COMMAND UP");
    // Motor control for right movement
    m = map(yValue,0,508,0,max);
    m = max-m;
    Serial.print(m);
    analogWrite(LPWM1, m);
    analogWrite(RPWM1, 0);
    analogWrite(LPWM2, 0);
    analogWrite(RPWM2, m);
  }

  else if (command & COMMAND_DOWN) {
    Serial.println("COMMAND DOWN");
    // Motor control for left movement
    m = map(yValue,508,1023,0,max);
    Serial.print(m);
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, m);
    analogWrite(LPWM2, m);
    analogWrite(RPWM2, 0);
  }

  else if (command & COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    // Motor control for forward movement
    m = map(xValue,508,1023,0,max);
    Serial.print(m);
    analogWrite(LPWM1, m);
    analogWrite(RPWM1, 0);
    analogWrite(LPWM2, m);
    analogWrite(RPWM2, 0);
  }

  else if (command & COMMAND_LEFT) {
    Serial.println("COMMAND LEFT");
    // Motor control for backward movement
    m = map(xValue,0,508,0,max);
    m = max-m;
    Serial.print(m);
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, m);
    analogWrite(LPWM2, 0);
    analogWrite(RPWM2, m);
  }

  


  // Stop the motors if no command is issued
  if (command == COMMAND_NO) {
    Serial.println("STOP MOTORS");
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 0);
    analogWrite(LPWM2, 0);
    analogWrite(RPWM2, 0);
  }
}