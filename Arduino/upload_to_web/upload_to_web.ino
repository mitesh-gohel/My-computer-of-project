

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *pwd = "12345678";
String s,x;


int value;          //Variable to store the incomming data


ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  s="<!DOCTYPE html><html><head></head><body><table border= 1px; bordercolor=\"/white\"; style=\"/width: 100%; background-color: Cyan; color: blue;\" ><tr style=\"/text-align: center\"><td ><h1 >Water level sensor </h1><font size=\"/5\"> <strong>water level :</strong>";
  s= s+ String(x);
 s= s+ "<br /> <br></font><div style=\"/float: center; margin-left: 120px\"><img src=\"/https://lh6.ggpht.com/AyI5C0xP9_Gpoic98l5W0zCpTM5t37KMh9Q8wUwlIiUMl4relilVQhpqsosFMRACu9g=w300\" width=\"/180\" height=\"/180\"></div></td><br/></td></tr></table></body><br/></td></tr></table></body>";
  server.send(200, "text/html",s );


  server.send(200, "text/html", s);
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid,pwd);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
value = analogRead(A0); //Read data from analog pin and store it to value variable
  Serial.println(value);
  if (value<=160){ 
    Serial.println("Water level: Low"); 
    x="Low";
    delay(1000);
  }
  else if (value>160 && value<=290){ 
    Serial.println("Water level: Medium"); 
    x="Medium";
    delay(1000);
  }
  else if (value>290){ 
    Serial.println("Water level: High"); 
    x="High";
    delay(1000);
  }

  
  server.handleClient();
}


