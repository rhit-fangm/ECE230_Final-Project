/*
File: dhtSensorFunctions
Author(s): Chase Robinson
Purpose: 
  read temperature and humidity
  values using the DHT11 sensor
  and update related global
  variables.
*/


// dht11 functions

/*
Function: updateDHTValues
Returns: nothing
Arguments: none
Purpose:
  update the global variables for temperature
  and humidity with the readings from the 
  DHT11 temperature and humidity sensor.
*/
void updateDHTValues(){
  temperature = dht11.readTemperature();
  humidity = dht11.readHumidity();
}

/*
Function: dhtValuesToSerial
Returns: nothing
Arguments: none
Purpose:
  refreshes the variables for temperature and
  humidity with a new reading and prints them
  in the serial monitor with labels for
  each number and a new line for separation.
*/
void dhtValuesToSerial(){
  updateDHTValues();
  Serial.print("dhtValues (T): ");
  Serial.print(temperature);
  Serial.print(" (H): ");
  Serial.print(humidity);
  Serial.println();
}

/*
Function: dhtConvertIntArray
Returns: nothing
Arguments: none
Purpose:
  There are two arrays, tempNums and humNums, of
  dimension 1x2 that are used respectively to store
  the first digit of each measurement in index 0 and
  the second digit in index 1. This function
  uses truncation to do that.
*/
void dhtConvertIntArray(){
  tempNums[0] = temperature / 10;
  tempNums[1] = temperature - ((temperature / 10)*10);
  humNums[0] = humidity / 10;
  humNums[1] = humidity - ((humidity / 10)*10);
}


// end dht functions
///-----------------------------