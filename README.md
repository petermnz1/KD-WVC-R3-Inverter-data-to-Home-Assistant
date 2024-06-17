# KD- WVC R3 Inverter Data to Home Assistant using MQTT
Getting local data from the WVC R3 Life edition inverters into Home Assistant.</br>
(Currently tested and working  on the WVC700 R3 Life Edition)</br>
Thanks to Damian Burrin for his project and all the information that got me started.</br>
https://github.com/damianburrin/WVC-Life-Edition-Data-Collector</br>
![Inverter R3](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/43dd78d5-4ea7-45e9-9242-6ab1fac1a9ab)
![Lid off](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/43542729-819f-49d6-9920-9e7a6f6f2b1a)

<b>Current understanding - thanks to Damian</b>
<p>The Wifi chip is a HF-LPT270 and fairly well documented online.</br> http://www.hi-flying.com/hf-lpt270 </br>and here </br> https://manuals.plus/m/5176309d280b9892c2bce6f24685fa4b934f7f79a321716bc0bc6c0f4dfe03bf_optim.pdf

![KD WVC UART WIFI chip pin out 2](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/0ef4d715-c879-44c2-bf84-569125182754)

<br>
The LIFE edition seems to have no connection from the UART RX to the J4 header on the board- I'm sure the UART takes an input in as you can power down and change the power limits remotely via the cloud intelligence app. I want to locally change the power level but I haven't worked this out yet so only Tx is connected to ESP32.

<p></br>It first makes a connection to the WIFI and It's server (alicloud) on power up</br></p>

<b>+ILOPCONNECT=WIFI_CONNECT</br>
+ILOPCONNECT=SERVER_CONNECT</b>

It Then sends a cycled serial connection on a permentent loop.

The Main data is sent</br>
<b>
AT+SENDICA=property,PV_Volt,50.8,PV_Current,1.09,PV_Power,55.4,AC_Volt,243.2,AC_Current,0.20,Out_Power,51.0,Temperature,30.0,Power_adjustment,100,Energy,94.89
+ok<br></br>
</b>
And then this additional data</br>
<b>
AT+SENDICA=property,PowerSwitch,1,Plant,0.16,Emission,0.09,Time,30,P_adj,66,TEMP_SET,67
+ok
</b></br><br>
or this - note the extra Daily value</br> 
<b>
AT+SENDICA=property,PowerSwitch,1,Daily,0.10,Plant,0.16,Emission,0.09,Time,30,P_adj,66,TEMP_SET,67
+ok</br>

I soldered to the HF-LPT270 UART TX and RX pins along with 3.3v and ground to power the ESP32 board.</br>
(Looking at photo I now see the soldering doesn't look good but it works :-))
![Inverter connection pins](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/8658950a-5c1c-4661-908d-2b0422e6b825)
</br>
</br>
I then tested UART output using Putty software on my pc with a cheap aliexpress USB to TTL reader.</br>
![USB to TTL](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/56448777-4f6f-43eb-bf32-e0955192f33f)</br>
These are the settings used.</br>
![image](https://github.com/petermnz1/KD-WVC-R3-Inverter-data-to-Home-Assistant/assets/91760855/63bae9db-117a-4bb6-82a7-06ade7099d56)</br>

Only Ground and HF-LPT270 UART TX to the USB-TTL RX are required to be connected.</br>
(MAKE SURE 3.3V is selected on the USB-TTL board or the magic smoke will appear.)
![UART reader](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/ac9df493-de3d-46f9-a456-889a6b4cccf6)

This is the data received.  Note: You only get data if a solar panel is connected and working (No data at night).
![Reader output on putty software](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/aacdd699-e53f-4673-ba47-b270e2f912db)

<b>Implementing The ESP32</b>
Using LOLIN ESP32 - A mini wifi boards based on WEMOS ESP32-S2FN4R2S2 called S2 mini about US$2  </b>
![image](https://github.com/petermnz1/KD-WVC-R3-Inverter-data-to-Home-Assistant/assets/91760855/50c66ad2-d07a-47cb-945d-dc95ee12eb36)

![Overview connection](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/23ae119b-c5d2-40c2-ba2c-c185eb4a7457)

Ground to GND, 3.3v to 3.3v and HF-LPT270 UART TX to the ESP32  RX (GPIO 37).</b>
![ESP32 LOLIN S2 connection](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/60f2f46d-1033-4f96-b0e2-a7e6fda64d99)

I've not connected from the HF-LPT270 UART RX pin of the Inverter to the ESP32 TX yet as when I do it stops sending data???</br>
I've not worked out why this occurs or what command to send to the Inverter yet to change the power setting.</br>
This is received when power adj command sent via phone app. </br>+ILOPDATA=ICA,Power_adjustment,100</br>
I'm hoping this is the echo of the change command???</br>

I then wrote the Arduino code with the help of ChatGPT and many hours trial and error.</br>
I'm no expert but it works surprising well.</br>
Below is the MQTT output. It updates approx every ~5 seconds.

![Inverter MQTT](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/c3ae1be8-b13b-4ee8-a39c-6e4fa1d080b5)

The uploaded code shows as separate files but they should be tabbed as below.
![image](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/f997d437-cbeb-49ca-809a-b2d49caab4e9)

Add  inverter.yaml to Home Assistant to see MQTT data.

![image](https://github.com/petermnz1/KD-WVC-R3-Inverter-/assets/91760855/52d0827c-fb84-49fa-b723-4045d9057658)


