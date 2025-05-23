
#define clockPin 18
#define shiftOutPin 2
#define regClear 4 //must be high to allow data (active-low clearing)
#define outEnable 5 //active low
const int shiftDelay = 0; //us

void setup() {
  // put your setup code here, to run once:
  pinMode(clockPin, OUTPUT);
  pinMode(shiftOutPin, OUTPUT);
  pinMode(regClear, OUTPUT);
  pinMode(outEnable, OUTPUT);
  //make sure clockPin is low initially
  digitalWrite(clockPin, LOW);
  
  digitalWrite(shiftOutPin, LOW);
  digitalWrite(regClear, HIGH);
  digitalWrite(outEnable, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  shiftOutBit(shiftOutPin, clockPin, regClear, outEnable, 1);
  for (int i = 0; i < 25 ; i++){
    shiftStep(clockPin);
    delay(200);
  }
}

//start clockPin low, toggle 1-0 to shift out, outEnable = active-low, regClearPin = active-low
void shiftOutBit(int shiftPin, int ClockPin, int regClearPin, int outEnablePin, bool bit){
  digitalWrite(shiftPin, bit);
  digitalWrite(ClockPin, HIGH);
  delayMicroseconds(shiftDelay);
  digitalWrite(ClockPin, LOW);
  digitalWrite(shiftPin, LOW);
}

//shifts registers by one
void shiftStep(int ClockPin){
  digitalWrite(ClockPin, HIGH);
  delayMicroseconds(shiftDelay);
  digitalWrite(ClockPin, LOW);
}
