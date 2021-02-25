int right_I = 13; // Air Input(Right)
int right_O = 12; // Air Output(Right)
int left_I = 9; // Air Input(Left)
int left_O = 10; // Air Output(Left)
int control_R = A0; // Trigger Input(Right)
int control_L = A1; // Trigger Input(Left)
int control_R_I; // Reading Right trigger signal
int control_L_I; // Reading left trigger signal
int count_R = 0; // 우측 활성화 변수
int count_L = 0; // 좌측 활성화 변수
int count_B = 0; // 양측 활성화 변수

// 우측 피드백 활성화
void RB(){
  digitalWrite(right_I, HIGH);
  delay(150);
  digitalWrite(right_I, LOW);
  count_R = 1;
  Serial.println("right");
  return;
}
// 우측 피드백 비활성화
void RBO(){
  digitalWrite(right_O,HIGH);
  delay(300);
  digitalWrite(right_O,LOW);
  count_R = 0;
  Serial.println("rightDOWN");
  return;
}

// 좌측 피드백 활성화
void LB(){
  digitalWrite(left_I, HIGH);
  delay(150);
  digitalWrite(left_I, LOW);
  count_L = 1;
  Serial.println("left");
  return;
}
// 좌측 피드백 비활성화
void LBO(){
  digitalWrite(left_O,HIGH);
  delay(300);
  digitalWrite(left_O, LOW);
  count_L = 0;
  Serial.println("leftDOWN");
  return;
}

// 양측 피드백 활성화
void both(){
  digitalWrite(left_I, HIGH);
  digitalWrite(right_I, HIGH);
  delay(150);
  digitalWrite(right_I, LOW);
  digitalWrite(left_I, LOW);
  count_B = 1;
  Serial.println("both");
  return;
}

// 양측 피드백 비활성화
void bothO(){
  digitalWrite(right_O,HIGH);
  digitalWrite(left_O,HIGH);
  delay(300);
  digitalWrite(left_O,LOW);
  digitalWrite(right_O,LOW);
  count_B = 0;
  Serial.println("bothDOWN");
  return;
}
// 양측 피드백 활성화 확인
void setBoth(){
  count_B = 1;
}
// 양측 비피드백 활성화 확인
void setSingle(){
  count_B = 0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(right_I, OUTPUT);
  pinMode(right_O, OUTPUT);
  pinMode(left_I, OUTPUT);
  pinMode(left_O, OUTPUT);
  pinMode(control_R, INPUT);
  pinMode(control_L, INPUT);
  Serial.begin(4800);
}

void loop() {
  // 양측 트리거 신호를 수치화
  control_R_I = analogRead(control_R);
  Serial.print("right : ");
  Serial.println(control_R_I);
  control_L_I = analogRead(control_L);
  Serial.print("left : ");
  Serial.println(control_L_I);
  
  //UP
  if((control_R_I > 900 and control_R_I <= 927) and (control_L_I > 900 and control_L_I <= 927) and count_R == 0){
    RB();
  }
  else if((control_R_I > 927 and control_R_I < 970) and (control_L_I > 927 and control_L_I < 970)and count_L == 0){
    LB();
  }
  else if(control_R_I >= 970 and control_L_I >= 970 and count_B == 0 and count_R == 1 and count_L == 0){
    LB();
    setBoth();
  }
  else if(control_R_I >= 970 and control_L_I >= 970 and count_B == 0 and count_R == 0 and count_L == 1){
    RB();
    setBoth();
  }
  else if(control_R_I >= 970 and control_L_I >= 970 and count_B == 0){
    both();
  }

  //DOWN
  if((control_R_I > 900 and control_R_I <= 927) and (control_L_I > 900 and control_L_I <= 927) and count_L == 1){
    setSingle();
    LBO();
  }
  else if((control_R_I > 927 and control_R_I < 970) and (control_L_I > 927 and control_L_I < 970)and count_R == 1){
    setSingle();
    RBO();
  }
  
  //DOWN2
  if(control_R_I < 890 and control_L_I < 890 and count_R == 1){
    RBO();
  }
  else if(control_R_I < 890 and control_L_I < 890 and count_L == 1){
    LBO();
  }
  else if(control_R_I < 890 and control_L_I < 890 and count_B == 1){
    bothO();
  }
}
