const int data_pin = 3;
const int shift_register_clock = 5;
const int latch_clock = 4;
int layerArray[5] = {1, 2, 4, 8, 16};
int maskArray[30] ={
    0x00000001, // Bit 0
    0x00000002, // Bit 1
    0x00000004, // Bit 2
    0x00000008, // Bit 3
    0x00000010, // Bit 4
    0x00000020, // Bit 5
    0x00000040, // Bit 6
    0x00000080, // Bit 7
    0x00000100, // Bit 8
    0x00000200, // Bit 9
    0x00000400, // Bit 10
    0x00000800, // Bit 11
    0x00001000, // Bit 12
    0x00002000, // Bit 13
    0x00004000, // Bit 14
    0x00008000, // Bit 15
    0x00010000, // Bit 16
    0x00020000, // Bit 17
    0x00040000, // Bit 18
    0x00080000, // Bit 19
    0x00100000, // Bit 20
    0x00200000, // Bit 21
    0x00400000, // Bit 22
    0x00800000, // Bit 23
    0x01000000, // Bit 24
    0x02000000, // Bit 25
    0x04000000, // Bit 26
    0x08000000, // Bit 27
    0x10000000, // Bit 28
    0x20000000  // Bit 29
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
  // SerialInput();
  controlCube(0x3FFFFFFF);
  for (int i = 0; i<25; i++) {
    controlCube(maskArray[i]);
    delay(100);
  }
 
}
 
void controlCube(int value){
  digitalWrite(latch_clock, LOW);
  value &= 0x3FFFFFFF;
 
  shiftOut(data_pin, shift_register_clock, MSBFIRST, (value >> 24) & 0xFF);
  shiftOut(data_pin, shift_register_clock, MSBFIRST, (value >> 16) & 0xFF);
  shiftOut(data_pin, shift_register_clock, MSBFIRST, (value >> 8) & 0xFF);
  shiftOut(data_pin, shift_register_clock, MSBFIRST, value & 0xFF);
 
  digitalWrite(latch_clock, HIGH);
}
 
void SerialInput(){
  // if (Serial.available() > 0) {
  //   String input = Serial.readStringUntil('\n');
  //   uint16_t value = input.toInt();
  //   controlCube(value);
  // }
   if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();  // remove whitespace
 
    // Convert to uint32_t using base 16
    uint32_t value = strtoul(input.c_str(), NULL, 16);
 
    Serial.print("You entered: 0x");
    Serial.println(value, HEX);
    Serial.print("Decimal: ");
    Serial.println(value);
 
    // Use it with your shift register:
    controlCube(value);
  }
}