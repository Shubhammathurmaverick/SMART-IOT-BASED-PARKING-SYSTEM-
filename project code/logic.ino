
void check_rfidcards()
{
//  inputString.trim();
  if (inputString.length() > 0)
  {
     if(inputString == user_1) 
     {
         if((park2_flag == 1) && (park1_flag == 1))
         {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SORRY!!!");
            lcd.setCursor(0, 1);
            lcd.print("Parking is FULL");
            tone_buzzer(1, 2000);
            inputString = "";
         }
         else
         {
            Serial.println("user_1");  
            send_data_string = String(3) + '*' + String(1);
            Serial.println("send_data_string = " + String(send_data_string)); 
            send_parameters();  
            receive_parameters();
            inputString = ""; 
            check_data();
         }

     }
     else if (inputString == user_2)
     {
          if((park2_flag == 1) && (park1_flag == 1))
         {
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("SORRY!!!");
           lcd.setCursor(0, 1);
           lcd.print("Parking is FULL");
           tone_buzzer(1, 2000);
           inputString = "";
         }
         else
         {
           Serial.println("user_2");    
           send_data_string = String(3) + '*' + String(2) ;
           Serial.println("send_data_string = " + String(send_data_string)); 
           send_parameters();
           receive_parameters();
           inputString = ""; 
           check_data();
         }
     }
     else if (inputString == user_3)
     {
         if((park2_flag == 1) && (park1_flag == 1))
         {
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("SORRY!!!");
           lcd.setCursor(0, 1);
           lcd.print("Parking is FULL");
           tone_buzzer(1, 2000);
           inputString = "";
         }
         else
         {
           Serial.println("user_3");   
           send_data_string = String(3) + '*' + String(3) ;
           Serial.println("send_data_string = " + String(send_data_string)); 
           send_parameters();
           receive_parameters();
           inputString = ""; 
           check_data();
         }
     }
     else if(inputString == handicap)
     {
         if(handicap_flag == 1)
         {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SORRY!!! HANDICAP");
            lcd.setCursor(0, 1);
            lcd.print("Parking is FULL");
            tone_buzzer(1, 2000);
            inputString = "";
         }
         else
         {
            Serial.println("user_4");   
            send_data_string = String(3) + '*' + String(4) ;
            Serial.println("send_data_string = " + String(send_data_string)); 
            send_parameters();
            receive_parameters();
            inputString = ""; 
            check_data();
         }
     }
     else if(inputString == truck)
     {
         if(truck_flag == 1)
         {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("SORRY!!!");
            lcd.setCursor(0, 1);
            lcd.print("TRUCK Parking FULL");
            tone_buzzer(1, 2000);
            inputString = "";
         }
         else
         {
            Serial.println("user_5");   
            send_data_string = String(3) + '*' + String(5) ;
            Serial.println("send_data_string = " + String(send_data_string)); 
            send_parameters();
            receive_parameters();
            inputString = ""; 
            check_data();  
         }      
     }
     else
     {
        Serial.println("Invalid Card");   
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Invalid Card");
        tone_buzzer(1, 2000);
        inputString = "";
     }
     inputString = "";
  }  
}

void checkslot()
{
  if (digitalRead(park1) == HIGH)
  {
    main_data[1] = (String)0;
    s_1 = "EMPTY";
    park1_flag = 0;
  }
  else
  {
    main_data[1] = (String)1;
    s_1 = "FULL";
    park1_flag = 1;
  }
  if (digitalRead(park2) == HIGH)
  {
    main_data[2] = (String) 0;
    s_2 = "EMPTY";
    park2_flag = 0;
  }
  else
  {
    main_data[2] = (String) 1;
    s_2 = "FULL";
    park2_flag = 1;
  }
  if (digitalRead(park3) == HIGH)
  {
    main_data[3] = (String)0;
    s_3 = "EMPTY";
    handicap_flag = 0;
  }
  else
  {
    main_data[3] =  (String)1;
    s_3 = "FULL";
    handicap_flag = 1;
  }
  if (digitalRead(park4) == HIGH)
  {
    main_data[4] = (String) 0;
    s_4 = "EMPTY";
    truck_flag = 0;
  }
  else
  {
    main_data[4] =  (String)1;
    s_4 = "FULL";
    truck_flag = 1;
  }
 
}

void check_data()
{
    if(serial_receiving_data == "true")
    { 
       digitalWrite(g_led, LOW);
       tone_buzzer(1, 500);
       entry_display();
       digitalWrite(m2_0, HIGH);
       digitalWrite(m2_1, LOW);
       delay(1500);
       digitalWrite(m2_0, LOW);
       digitalWrite(m2_1, LOW);
       delay(4000);
       tone_buzzer(1, 500);
       digitalWrite(m2_0, LOW);
       digitalWrite(m2_1, HIGH);
       delay(1500);
       digitalWrite(m2_0, LOW);
       digitalWrite(m2_1, LOW);
       digitalWrite(g_led, HIGH);
       serial_receiving_data = "";
    }
    if(serial_receiving_data == "Lowb")
    {  
       digitalWrite(r_led, LOW);
       balance_low_disp();
       serial_receiving_data = "";
       tone_buzzer(1, 2000);
       checkslot();
       send_data_string = String(2) + '*' + main_data[1] + '*' + main_data[2] + '*' + main_data[3] + '*' + main_data[4]; 
       send_parameters();
       delay(4000);
       digitalWrite(r_led, HIGH);
    }  
}
