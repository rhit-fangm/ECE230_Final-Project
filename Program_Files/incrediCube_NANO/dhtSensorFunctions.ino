/*
File: dhtSensorFunctions
Author(s): Chase Robinson
Purpose: 
  read temperature and humidity
  values using the DHT11 sensor.
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

void dhtConvertIntArray(int tempNumArray[2], int humNumArray[2]){
  tempNumArray[0] = temperature / 10;
  tempNumArray[1] = temperature - ((temperature / 10)*10);
  humNumArray[0] = humidity / 10;
  humNumArray[1] = humidity - ((humidity / 10)*10);
}


// end dht functions
///-----------------------------