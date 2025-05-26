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

void dhtConvertIntArray(){
  tempNums[0] = temperature / 10;
  tempNums[1] = temperature - ((temperature / 10)*10);
  humNums[0] = humidity / 10;
  humNums[1] = humidity - ((humidity / 10)*10);
}


// end dht functions
///-----------------------------