
#include <ESP8266WiFi.h>

const char* ssid = "mitesh";
const char* password = "12345678";

const char* host = "mitesh690.000webhostapp.com";


String s,x,y,z;
int value; 

int i=1;
int k=1;

int m=1;
int n=1;


void setup() {
  Serial.begin(9600);

  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
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

void loop() {
  z="70";

  value = analogRead(A0); //Read data from analog pin and store it to value variable
  Serial.println(value);
  if (value<=160){ 
    Serial.println("Water level: Low"); 
    x="Low";
    y="25";
    delay(1000);
  }
  else if (value>160 && value<=290){ 
    Serial.println("Water level: Medium"); 
    x="Medium";
    y="50";
   delay(1000);
    }
  else if (value>160){ 
    Serial.println("Water level: High"); 
    x="HIGH";
    y="75";
   delay(1000);
  }




  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
   
  }

 
  // Prepare the response
   s = "GET /index.php?water=";
   s += String(x);
   s += "&waterpercentage=";
   s += String(y);
   s += "&flow=";
   s += String(z);
   s += " HTTP/1.1\r\nHost: mitesh690.000webhostapp.com\r\n\r\n";

 
  // Send the response to the client
  client.print(s);
  delay(500);

  int a=0;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){a++;
   String line = client.readStringUntil('\n');

//if(A==9){
Serial.print(a);
Serial.print("==");
Serial.println(line);
//}
   


  Serial.println("Client disonnected");


}
}


