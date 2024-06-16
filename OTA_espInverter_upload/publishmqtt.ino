void publishmqtt1(){// convert float to string
      dtostrf((WiFi.RSSI()),5,2,Rxrssi_str);
      //dtostrf(bootCount,5,2,bootCount_str);
      //send mqtt messages
      client.publish("tele/Inverter/Rxrssi", Rxrssi_str);
      //client.publish("tele/Inverter/RxData", RxData.c_str());//test only
      // Form the MQTT topic string
      topic = "tele/Inverter/" + data_rx_array[1];               // Form the MQTT topic string
      client.publish(topic.c_str(), data_rx_array[2].c_str());   // Send mqtt messages
      topic = "tele/Inverter/" + data_rx_array[3];
      client.publish(topic.c_str(), data_rx_array[4].c_str());
      topic = "tele/Inverter/" + data_rx_array[5];
      client.publish(topic.c_str(), data_rx_array[6].c_str());
      topic = "tele/Inverter/" + data_rx_array[7];
      client.publish(topic.c_str(), data_rx_array[8].c_str());
      topic = "tele/Inverter/" + data_rx_array[9];
      client.publish(topic.c_str(), data_rx_array[10].c_str());
      topic = "tele/Inverter/" + data_rx_array[11];
      client.publish(topic.c_str(), data_rx_array[12].c_str());
      topic = "tele/Inverter/" + data_rx_array[13];
      client.publish(topic.c_str(), data_rx_array[14].c_str());
      topic = "tele/Inverter/" + data_rx_array[15];
      client.publish(topic.c_str(), data_rx_array[16].c_str());
      topic = "tele/Inverter/" + data_rx_array[17];
      client.publish(topic.c_str(), data_rx_array[18].c_str());
      
      Serial.println("Published Mqtt1 messages ");
}
void publishmqtt2(){// convert float to string
      
      topic = "tele/Inverter/" + data_rx_array[19];
      client.publish(topic.c_str(), data_rx_array[20].c_str());
      topic = "tele/Inverter/" + data_rx_array[21];
      client.publish(topic.c_str(), data_rx_array[22].c_str());
      topic = "tele/Inverter/" + data_rx_array[23];
      client.publish(topic.c_str(), data_rx_array[24].c_str());
      topic = "tele/Inverter/" + data_rx_array[25];
      client.publish(topic.c_str(), data_rx_array[26].c_str());
      topic = "tele/Inverter/" + data_rx_array[27];
      client.publish(topic.c_str(), data_rx_array[28].c_str());
      topic = "tele/Inverter/" + data_rx_array[29];
      client.publish(topic.c_str(), data_rx_array[30].c_str());
      
      Serial.println("Published Mqtt 2 messages ");
}

 void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    client.connect("inverterClient", "mqtt user", "oscar"); 
    wait(1000);
    Serial.print("Attempting MQTT reconnection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 10 seconds");
      wait(10000);
    }
  }
}
