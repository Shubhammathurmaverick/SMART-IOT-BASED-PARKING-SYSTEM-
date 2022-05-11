#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 
#include <TimerOne.h>

#define esp_baudrate 115200
bool notConected = true;
bool login = false;
int iot_status;

String id = "vrushankshah.vs@gmail.com"; // iotgecko login id
String pass = "1763"; // iotgecko login password4363
String ssid = "iot";//SSID/name of your wifi router or wifi hotspot
String pass_key = "project1234"; // Wifi password

SoftwareSerial esp8266(8, 7);     // rx,tx for esp8266
LiquidCrystal_I2C lcd(0x20, 20, 4);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
SoftwareSerial rfid1(4, 0);

String user_1 = "3B00381F8D91";
String user_2 = "3B003B3B1D26";
String user_3 = "3B003B3B0833";
String handicap = "3B00381EFDE0";
String truck = "3B00381F9A86";

String send_data_string;      
String Command;
String inputString = "";
String s_1; 
String s_2; 
String s_3; 
String s_4; 
     
const int rx1 = A1;
const int rx2 = 10;
const int m1_0 = A3;
const int m1_1 = A2;
const int m2_0 = 2;
const int m2_1 = 3;
const int g_led = 9;
const int r_led = 5;
const int buzzer = 6;
long previous_millis = 0;

const int park1 = 11;
const int park2 = 12;
const int park3 = 13;
const int park4 = A0;
volatile byte entry_flag;
volatile byte exit_flag;

unsigned char handicap_flag = 0;
unsigned char truck_flag = 0;
unsigned char park1_flag = 0;
unsigned char park2_flag = 0;

String serial_receiving_data;
char i;
int lastparking;
String main_data[10];


void setup()
{
   Serial.begin(9600); // your esp's baud rate might be different
   esp8266.begin(9600);
   rfid1.begin(9600);
   pinMode(rx1, INPUT);
   pinMode(rx2, INPUT);
   pinMode(park1, INPUT);
   pinMode(park2, INPUT);
   pinMode(park3, INPUT);
   pinMode(park4, INPUT);
   
   pinMode(m1_0, OUTPUT);
   pinMode(m1_1, OUTPUT);
   pinMode(m2_0, OUTPUT);
   pinMode(m2_1, OUTPUT);
   pinMode(g_led, OUTPUT);
   digitalWrite(g_led, LOW);
   pinMode(r_led, OUTPUT);
   digitalWrite(r_led, HIGH);
   pinMode(buzzer, OUTPUT);
   digitalWrite(buzzer, HIGH);
   digitalWrite(g_led, HIGH);
   delay(500);
   digitalWrite(buzzer, LOW);
   lcd.init();
   main_page();
   delay(3000);
   digitalWrite(m1_0, LOW);
   digitalWrite(m1_1, LOW);
   digitalWrite(m2_0, LOW);
   digitalWrite(m2_1, LOW);
   Timer1.initialize(100000);         // initialize timer1, and set a 1 second period
   Timer1.attachInterrupt(checkIR);
}

void loop()
{
   while(1)
   {
     if (entry_flag == 1)
     {
        while(entry_flag == 1)
        {
           tone_buzzer(1, 150);
           lcd.clear();
           lcd.print(F("Checking for empty"));
           lcd.setCursor(0, 1);
           lcd.print(F("       Slots"));
           checkslot();
           delay(2000);
           if((park1_flag == 1) && (park2_flag == 1) && (handicap_flag == 1) && (truck_flag == 1))
           {
               display_slot_full();
               entry_flag = 0;
               send_data_string = String(2) + '*' + main_data[1] + '*' + main_data[2] + '*' + main_data[3] + '*' + main_data[4]; 
               send_parameters();
               delay(4000);
           }
           else
           {
             tone_buzzer(2, 250);
             lcd.clear();
             display_slot();
             lcd.setCursor(0, 2);
             lcd.print(F("Please Tap Your"));
             lcd.setCursor(0, 3);
             lcd.print(F("RFID Card..."));
             inputString = "";
             delay(1000);
             rfid1.begin(9600);
             rfid1.listen();
             while (rfid1.available() <= 0);
             tone_buzzer(1, 1000);
             while (rfid1.available()) 
             {
               delay(2);  //delay to allow byte to arrive in input buffer
               char c = rfid1.read();
               inputString += c;
              }
              inputString = inputString.substring(0,12);
              inputString.trim();
              Serial.println("inputString1");
              Serial.println(inputString);
              delay(1000);
              check_rfidcards();
              entry_flag = 0;
              delay(2000);
              send_data_string = String(2) + '*' + main_data[1] + '*' + main_data[2] + '*' + main_data[3] + '*' + main_data[4]; 
              send_parameters();
           }
        }
     }
     else if(exit_flag == 1)
     {
         digitalWrite(g_led, LOW);
         tone_buzzer(1, 500);
         digitalWrite(m1_0, HIGH);
         digitalWrite(m1_1, LOW);
         delay(1500);
         digitalWrite(m1_0, LOW);
         digitalWrite(m1_1, LOW);
         delay(2000);
         lcd.clear();
         lcd.print("Good bye..");
         lcd.setCursor(0, 1);
         lcd.print("Have a Nice day.");
         delay(2000);
         tone_buzzer(1, 500);
         digitalWrite(m1_0, LOW);
         digitalWrite(m1_1, HIGH);
         delay(1500);
         digitalWrite(m1_0, LOW);
         digitalWrite(m1_1, LOW);
         digitalWrite(g_led, HIGH);
         tone_buzzer(1, 500);
         checkslot();
         send_data_string = String(2) + '*' + main_data[1] + '*' + main_data[2] + '*' + main_data[3] + '*' + main_data[4]; 
         send_parameters();
         exit_flag = 0;
     }
     else
     {
        main_page();
     } 
     if (millis() - previous_millis > 20000)
     {
       checkslot();
       send_data_string = String(2) + '*' + main_data[1] + '*' + main_data[2] + '*' + main_data[3] + '*' + main_data[4]; 
       send_parameters();
       previous_millis = millis();
     }
     delay(200);
    }
}

void checkIR()
{
    if ((digitalRead(rx1) ==  HIGH))
    {
        entry_flag = 1;
    }
    if ((digitalRead(rx2) ==  HIGH))
    {
        exit_flag = 1;
    }
}

void tone_buzzer(int i, int d)
{
  for (int j = 0; j < i; j++)
  {
    digitalWrite(buzzer, HIGH);
    delay(d / 2);
    analogWrite(buzzer, LOW);
    delay(d / 2);
  }
}
