
void send_parameters()
{
  esp8266.listen();
  esp8266.print(send_data_string);
  esp8266.end(); 
}

void receive_parameters()
{
  esp8266.listen();
  while (esp8266.available() <= 0 )
  {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Please Wait..."));
      lcd.setCursor(0,1);
      lcd.print(F("Checking for Balance"));
      delay(1000);
  };
  if(esp8266.available() > 0)
  {
      Serial.println("here data");
      serial_receiving_data = esp8266.readString();
      Serial.print("esp tx= " + String(serial_receiving_data));
  }
  esp8266.end();
}
