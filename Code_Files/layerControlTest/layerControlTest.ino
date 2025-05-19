const int data_pin = 3;
const int shift_register_clock = 5;
const int latch_clock = 4;
int layerArray[5] = {1, 2, 4, 8, 16};
int columnArray[25] ={
    0x00000001,  // bit 1
    0x00000002,  // bit 2
    0x00000004,  // bit 3
    0x00000008,  // bit 4
    0x00000010,  // bit 5
    0x00000020,  // bit 6
    0x00000040,  // bit 7
    0x00000080,  // bit 8
    0x00000100,  // bit 9
    0x00000200,  // bit 10
    0x00000400,  // bit 11
    0x00000800,  // bit 12
    0x00001000,  // bit 13
    0x00002000,  // bit 14
    0x00004000,  // bit 15
    0x00008000,  // bit 16
    0x00010000,  // bit 17
    0x00020000,  // bit 18
    0x00040000,  // bit 19
    0x00080000,  // bit 20
    0x00100000,  // bit 21
    0x00200000,  // bit 22
    0x00400000,  // bit 23
    0x00800000,  // bit 24
    0x01000000   // bit 25
};

void setup() {
  // put your setup code here, to run once:
  pinMode(data_pin, OUTPUT);
  pinMode(shift_register_clock, OUTPUT);
  pinMode(latch_clock, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  controlLayers(1);
  
}

void controlLayers(int layerNumber){
  digitalWrite(latch_clock, LOW);
  shiftOut(data_pin, shift_register_clock, MSBFIRST, layerArray[layerNumber]);
  digitalWrite(latch_clock, HIGH); 
}