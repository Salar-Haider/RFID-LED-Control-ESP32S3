#include <SPI.h>
#include <MFRC522.h>

// Pin configuration for ESP32-S3
#define SS_PIN    10   // SDA pin on RC522
#define RST_PIN    9   // Reset pin
#define SCK_PIN   12   // Clock pin
#define MOSI_PIN  11
#define MISO_PIN  13
#define LED_PIN   15   // LED pin

MFRC522 rfid(SS_PIN, RST_PIN);

// Define card UIDs
byte card1UID[4] = {0xB3, 0x0A, 0xF9, 0x05}; // first card
byte card2UID[4] = {0xBD, 0x25, 0x73, 0x06}; // second card

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nRC522 RFID LED Control Starting...");

  // Setup LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // default off

  // Start SPI with custom pins
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN);

  // Initialize RC522
  rfid.PCD_Init();
  delay(50);

  Serial.println("RC522 initialized. Scan your card...\n");
}

// Compare two UID arrays
bool isCard(byte *uid, byte *targetUID, byte length) {
  for (byte i = 0; i < length; i++) {
    if (uid[i] != targetUID[i]) return false;
  }
  return true;
}

void loop() {
  // Look for a new card
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.println("Card detected!");

  // Print UID
  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Check which card it is
  if (isCard(rfid.uid.uidByte, card1UID, 4)) {
    Serial.println("Card 1 detected: LED ON");
    digitalWrite(LED_PIN, HIGH);
  } 
  else if (isCard(rfid.uid.uidByte, card2UID, 4)) {
    Serial.println("Card 2 detected: LED OFF");
    digitalWrite(LED_PIN, LOW);
  } 
  else {
    Serial.println("Unknown card.");
  }

  Serial.println("----------------------------");

  // Halt PICC (stop communication)
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(500); // small delay before scanning again
}
