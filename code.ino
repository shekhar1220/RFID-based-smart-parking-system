#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
BlynkTimer timer;

#define RST_PIN 34 // Configurable, see typical pin layout above
#define SS_PIN 2 // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
uint8_t j = 0; // Variable used for counter

String user1 = "B7 87 43 D6";
String user2 = "A7 92 6A D7";

int travled_time = 0;
int travled_time2 = 0;

int amount = 2;

int start_count = 0;
int start_count2 = 0;

int u1 = 0;
int u2 = 0;

void setup()
{
Serial.begin(9600);
SPI.begin(); // Initiate SPI bus
mfrc522.PCD_Init();
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Started");
delay(2000);
timer.setInterval(500, rfid);
timer.setInterval(1000, cal_time);
}

void cal_time()
{
if(start_count == 1)
{
travled_time += 1;
Serial.println("1 Total Time:" + String(travled_time));
}
else if(start_count2 == 1)
{
travled_time2 += 1;
Serial.println("2 Total Time:" + String(travled_time2));
}
}

void rfid()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Scan Tag");
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}
if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}
String content = "";
for (byte i = 0; i < mfrc522.uid.size; i++)
{
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
content.toUpperCase();
Serial.println(content.substring(1));
if (content.substring(1) == user1 && u1 == 0)
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("1 Started");
start_count = 1;
u1 = 1;
delay(1000);
}
else if (content.substring(1) == user1 && u1 == 1)
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("1 Ended");
start_count = 0;
u1 = 0;
display_fare(1);
delay(1000);
}
else if (content.substring(1) == user2 && u2 == 0)
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("2 Started");
start_count2 = 1;
u2 = 1;
delay(1000);
}
else if (content.substring(1) == user2 && u2 == 1)
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("2 Ended");
start_count2 = 0;
u2 = 0;
display_fare(2);
delay(1000);
}
else
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Unknown Card");
lcd.setCursor(0, 1);
lcd.print("Access denied");
delay(1000);
lcd.clear();
}
}

void display_fare(int user)
{
if(user == 1)
{
float mins = travled_time / 60; //convert seconds to minutes
float charges = mins * amount;
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Travl Time:" + String(mins) + "m");
lcd.setCursor(0, 1);
lcd.print("Amt Charged:" + String(charges));
travled_time = 0;
delay(2000);
}
else if(user == 2)
{
float mins = travled_time2 / 60; //convert seconds to minutes
float charges = mins * amount;
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Travl Time:" + String(mins) + "m");
lcd.setCursor(0, 1);
lcd.print("Amt Charged:" + String(charges));
travled_time2 = 0;
delay(2000);
}
}

void loop()
{
timer.run();
}
