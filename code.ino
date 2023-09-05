#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

BlynkTimer timer;
#define RST_PIN 34 // Configurable
#define SS_PIN 2 // Configurable

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

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