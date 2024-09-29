#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

char command;  // Store a single character instead of a string
ESP8266WebServer server(80);

void setup() {
   Serial.begin(115200);   
   WiFi.mode(WIFI_AP);
   WiFi.softAP("MK15","Tonystark");

   IPAddress myIP = WiFi.softAPIP();  
   // Starting WEB-server 
   server.begin();    
}

void loop() {
  server.handleClient();
  
  if (server.hasArg("State")) {  // Check if the client has sent the "State" argument
    String receivedCommand = server.arg("State");  // Get the command as a string

    if (receivedCommand.length() > 0) {
      command = receivedCommand[0];  // Extract the first character from the string
      // Serial.print("Received Command: ");
    //   Serial.println(command);  // Print the received character

      // Handle the received character
      switch (command) {
        case 'F':
          Serial.println("F");
          Serial.println("S");
          break;
        case 'B':
          Serial.println("B");
          Serial.println("S");
          break;
        case 'R':
          Serial.println("R");
          Serial.println("S");
          break;
        case 'L':
          Serial.println("L");
          Serial.println("S");
          break;
        case 'S':
          Serial.println("S");
          break;
        case 'G':
          Serial.println("G");
          break;
        case 'P':
          Serial.println("P");
          break;
        case 'U':
          Serial.println("U");
          break;
        case 'M':
          Serial.println("M");
          break;
        case 'D':
          Serial.println("D");
          break;
        case 'O':
          Serial.println("O");
          break;           
        case 'C':
          Serial.println("C");
          break;
        case '0':
          Serial.println("0");
          break;                                                                
      }
    }
  }
}
