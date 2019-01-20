bool past[3] = {false, false, false};
bool present[3] = {false, false, false};
unsigned long timer = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);
}

char getLetter(byte letter, bool cap = false) {
  switch(letter)
  {
    case 0b00100000:
      return cap ? 'A' : 'a';
      break;
    case 0b00110000:
      return cap ? 'B' : 'b';
      break;
    case 0b00100100:
      return cap ? 'C' : 'c';
      break;
    case 0b00100110:
      return cap ? 'D' : 'd';
      break;
    case 0b00100010:
      return cap ? 'E' : 'e';
      break;
    case 0b00110100:
      return cap ? 'F' : 'f';
      break;
    case 0b00110110:
      return cap ? 'G' : 'g';
      break;
    case 0b00110010:
      return cap ? 'H' : 'h';
      break;
    case 0b00010100:
      return cap ? 'I' : 'i';
      break;
    case 0b00010110:
      return cap ? 'J' : 'j';
      break;
    case 0b00101000:
      return cap ? 'K' : 'k';
      break;
    case 0b00111000:
      return cap ? 'L' : 'l';
      break;
    case 0b00101100:
      return cap ? 'M' : 'm';
      break;
    case 0b00101110:
      return cap ? 'N' : 'n';
      break;
    case 0b00101010:
      return cap ? 'O' : 'o';
      break;
    case 0b00111100:
      return cap ? 'P' : 'p';
      break;
    case 0b00111110:
      return cap ? 'Q' : 'q';
      break;
    case 0b00111010:
      return cap ? 'R' : 'r';
      break;
    case 0b00011100:
      return cap ? 'S' : 's';
      break;
    case 0b00011110:
      return cap ? 'T' : 't';
      break;
    case 0b00101001:
      return cap ? 'U' : 'u';
      break;
    case 0b00111001:
      return cap ? 'V' : 'v';
      break;
    case 0b00010111:
      return cap ? 'W' : 'w';
      break;
    case 0b00101101:
      return cap ? 'X' : 'x';
      break;
    case 0b00101111:
      return cap ? 'Y' : 'y';
      break;
    case 0b00101011:
      return cap ? 'Z' : 'z';
      break;
    case 0b00010000:
      return ',';
      break;
    case 0b00010011:
      return '.';
      break;
    default:
      return ' ';
      break;
  }
}

char getNumber(byte number) {
  switch(number)
  {
    case 0b00100000:
      return '1';
      break;
    case 0b00110000:
      return '2';
      break;
    case 0b00100100:
      return '3';
      break;
    case 0b00100110:
      return '4';
      break;
    case 0b00100010:
      return '5';
      break;
    case 0b00110100:
      return '6';
      break;
    case 0b00110110:
      return '7';
      break;
    case 0b00110010:
      return '8';
      break;
    case 0b00010100:
      return '9';
      break;
    case 0b00010110:
      return '0';
      break;
    default:
      return ' ';
      break;
  }
}

byte getCode() {
  byte letter = 0b00000000;
  
  do {
    present[0] = analogRead(A0) > 512;
    present[1] = analogRead(A1) > 512;
    present[2] = analogRead(A2) > 512;
  } while(!present[0] && !present[1] && !present[2]);

  past[0] = present[0];
  past[1] = present[1];
  past[2] = present[2];
  do {
    if(!past[0]) past[0] = present[0];
    if(!past[1]) past[1] = present[1];
    if(!past[2]) past[2] = present[2];
    present[0] = analogRead(A0) > 512;
    present[1] = analogRead(A1) > 512;
    present[2] = analogRead(A2) > 512;
  } while(present[0] || present[1] || present[2]);
  letter += past[0] ? 0b00100000 : 0b00000000;
  letter += past[1] ? 0b00010000 : 0b00000000;
  letter += past[2] ? 0b00001000 : 0b00000000;
  
  timer = millis(); 
  do {
    present[0] = analogRead(A0) > 512;
    present[1] = analogRead(A1) > 512;
    present[2] = analogRead(A2) > 512;
  } while(millis() - timer < 1000 && !present[0] && !present[1] && !present[2]);

  if(millis() - timer < 1000) {
    past[0] = present[0];
    past[1] = present[1];
    past[2] = present[2];
    do {
      if(!past[0]) past[0] = present[0];
      if(!past[1]) past[1] = present[1];
      if(!past[2]) past[2] = present[2];
      present[0] = analogRead(A0) > 512;
      present[1] = analogRead(A1) > 512;
      present[2] = analogRead(A2) > 512;
    } while(present[0] || present[1] || present[2]);
    
    letter += past[0] ? 0b00000100 : 0b00000000;
    letter += past[1] ? 0b00000010 : 0b00000000;
    letter += past[2] ? 0b00000001 : 0b00000000;
  }
    
  return letter;
}

void loop() {
  byte letter = getCode();
  if(letter == 0b00001111)
    Serial.print(getNumber(getCode()));
//  else if(letter == 0b00000001)
//    Serial.print(getLetter(getCode(), true));
  else Serial.print(getLetter(letter));
}
