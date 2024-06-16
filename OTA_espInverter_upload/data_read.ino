void Data_read(){  
//Receive data and return it
while (MySerial.available())
  {
     c = MySerial.read();
     RxData += c;
     RxData.trim(); // Remove any trailing newline characters
  while ((commaIndex = RxData.indexOf(',')) > 0)
     {
        data_rx_array[i++] = RxData.substring(0, commaIndex);
        RxData = RxData.substring(commaIndex + 1);
      }
      data_rx_array[i] = RxData; // Add the last element  
    }
// Check if the first element matches the expected value
if (data_rx_array[0] == "AT+SENDICA=property")
     {
    // Check if the second element matches "PV_Volt"
    if (data_rx_array[1] == "PV_Volt") 
       {
        String mod_last_element = data_rx_array[18];
        data_rx_array[18] = mod_last_element.substring(0, 5); // Trim the trailing newline characters 
       } 
       publishmqtt1();    
     }  
//Check for second string  
if (RxData.substring(0, 7) == ",PowerS") {
    RxData = RxData.substring(1);// remove comma at start of string
    while ((commaIndex = RxData.indexOf(',')) > 0)
      {
        data_rx_array[i++] = RxData.substring(0, commaIndex);
        RxData = RxData.substring(commaIndex + 1);
      }
        String mod_last_element = data_rx_array[30];
        data_rx_array[30] = mod_last_element.substring(0, 5); // Trim the trailing newline characters    
        publishmqtt2();
    }  
   wait(1000);    
   RxData = "";
   c = 0,i = 0;
}
   //  AT+SENDICA=property,PV_Volt,50.8,PV_Current,1.09,
   //  PV_Power,55.4,AC_Volt,243.2,AC_Current,0.20,
   //  Out_Power,51.0,Temperature,30.0,Power_adjustment,100,
   //  Energy,94.89 +ok
