/*
File: dhtSensorFunctions
Author(s): Chase Robinson, Michael Fang
Purpose: do stuff using DHT11
*/


// dht11 functions
void updateDHTValues(){
  temperature = dht11.readTemperature();
  humidity = dht11.readHumidity();
}

void dhtValuesToSerial(){
  updateDHTValues();
  Serial.print("dhtValues (T): ");
  Serial.print(temperature);
  Serial.print(" (H): ");
  Serial.print(humidity);
  Serial.println();
}


// end dht functions
///-----------------------------