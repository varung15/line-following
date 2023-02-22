int P, D, I, previousError, PIDvalue, error;
int lsp = 100;
int rsp = 100;
int lfspeed = 125;
float Kp = 0.07;
float Kd = 0.05;
float Ki = 0;
void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}
void loop() {
  if (analogRead(2) > 400)  //Replace 400 with the threshold that you have calculated
  {
    linefollow();
    digitalWrite(3, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  } else if (lsp > rsp) {
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    analogWrite(9, 0);
    analogWrite(10, 200);
  } else if (rsp > lsp) {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(9, 200);
    analogWrite(10, 0);
  }
}
void linefollow() {
  int error = analogRead(1) - analogRead(3);
  P = error;
  I = I + error;
  D = error - previousError;
  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;
  lsp = lfspeed - PIDvalue;
  rsp = lfspeed + PIDvalue;
  if (lsp > 200) { lsp = 200; }
  if (lsp < 0) { lsp = 0; }
  if (rsp > 200) { rsp = 200; }
  if (rsp < 0) { rsp = 0; }
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  analogWrite(9, rsp);
  analogWrite(10, lsp);
}