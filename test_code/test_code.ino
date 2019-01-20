#define HIGH_LOW_DIFF 512

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  int dot0 = analogRead(A0);
  int dot1 = analogRead(A1);
  int dot2 = analogRead(A2);
  
  digitalWrite(10, (dot0 > 512) ? HIGH : LOW);
  digitalWrite(11, (dot1 > 512) ? HIGH : LOW);
  digitalWrite(12, (dot2 > 512) ? HIGH : LOW);
  
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.println(analogRead(A2));3
}
