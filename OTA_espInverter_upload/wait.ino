void wait(int t) // Use this instead of delay (delay stops program running)
{
  long time = millis()+t;
  while(millis()<time)
  {
      ArduinoOTA.handle();
  }
}
