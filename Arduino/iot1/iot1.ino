
#include <ESP8266WiFi.h>
#include <Wire.h>  // This library is already built in to the Arduino IDE

const char* ssid = "PATEL'S iPHONE"; // put your router name
const char* password = "patel123";// put your password 
 
const char* host = "watermanagementsystem.000webhostapp.com";





 
void setup() {
  Serial.begin(9600);
  delay(100);
  delay(200);
 
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  


  // Print the IP address
  Serial.println(WiFi.localIP());
}
 
int value = 0;




 
void loop() {
 
 

  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
   
  }
  
  // We now create a URI for the request
  String url = "/Dharmesh.html";
 
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  int i=0;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){i++;
   String line = client.readStringUntil('\n');

//if(i==9){
Serial.print(i);
Serial.print("==");
Serial.println(line);
//}


}
    
 //   Serial.println(line);
 
  
  Serial.println();



  delay(2000);

  
   delay(1000); 
    // Enable or Turn On the backlight 
  delay(800);
 
   delay(500); 
 // Enable or Turn On the backlight 
  delay(400);

  delay(300); 
  delay(150);
    
   delay(100); 
   // Enable or Turn On the backlight 
  
  
 
  
 
  
 
  
 
 
}
