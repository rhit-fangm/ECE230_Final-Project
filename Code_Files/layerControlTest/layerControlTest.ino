const int data_pin = 3;
const int shift_register_clock = 5;
const int latch_clock = 4;
int layerArray[5] = {1, 2, 4, 8, 16};

void setup() {
  // put your setup code here, to run once:
  pinMode(data_pin, OUTPUT);
  pinMode(shift_register_clock, OUTPUT);
  pinMode(latch_clock, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  controlLayers(4);
  
}

void controlLayers(int layerNumber){
  digitalWrite(latch_clock, LOW);
  shiftOut(data_pin, shift_register_clock, MSBFIRST, layerArray[layerNumber]);
  digitalWrite(latch_clock, HIGH); 
}