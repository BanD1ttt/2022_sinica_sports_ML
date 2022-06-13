#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 22
#define SS_PIN 5
#define Buz1 12
#define UID_1 109
#define UID_2 113
#define UID_3 117
#define UID_4 121

MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() {
  Serial.begin(115200);
  SPI.begin();
  pinMode(Buz1, OUTPUT);
  /* Initialize MFRC-522 and send version info to serial port (can be seen in serial monitor of arduino IDE)
   */
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan UID"));
}
byte uid_detect = 0;
void loop() {
  uid_detect = 0;
  /*  PICC_IsNewCardPresent() is to detect card and 
   *  if there is no card, restart the loop()
   */
  if(!mfrc522.PICC_IsNewCardPresent()){
    return;  
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }
  /*Show information of card ID */
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  
  /* sum up the ID value */
  for(int i = 0; i < 8; i++){
    uid_detect += mfrc522.uid.uidByte[i];
  } 
  /* see the detected ID is what we want, now I just set every ID 
   * will be detected so the buzzer will be trigger for every ID tag
   */
  switch(uid_detect){
    case UID_1:
    case UID_2:
    case UID_3:
    case UID_4:
      {
        Serial.println("detected");
        digitalWrite(Buz1, HIGH);
        delay(100);
        digitalWrite(Buz1, LOW);
      }
      break;
  }
  Serial.println(uid_detect);
}
