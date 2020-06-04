
#include <ESP8266WiFi.h>

const char* ssid = "mitesh";
const char* password = "12345678";

String s,t,u,v;
 

                                      


WiFiServer server(80);

void setup() {
  Serial.begin(9600);





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
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {


  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
    
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  

  // Prepare the response
  s = "<!DOCTYPE html>";
  s += "<html>";
   s += "<head>";
  s += "<style>";
 s += "</style>";
 s += "<script>";
 s += "function redraw(";
 s += "{";
 s += "draw(document.getElementById("myList").value);";
 s += "}";
 s += "function draw(speed)";
 s += "{";
 s += "var  canvas = document.getElementById("myCanvas");";
 s += "var  context = canvas.getContext("2d");";
 s += "context.clearRect(0,0,canvas.width, canvas.height);";
 s += "var centerX = canvas.width / 2;";
 s += "var centerY = canvas.height / 2;";
  s += "var radius = canvas.height / 2 - 20;";
  s += "context.beginPath();"; 
 s += "context.arc(centerX, centerY, radius, Math.PI*0.10, Math.PI*-1.1, true);"; 
 s += "var gradience = context.createRadialGradient(centerX, centerY, radius-radius/2, centerX, centerY, radius-radius/8);"; 
 s += "gradience.addColorStop(0, '#ff9000');"; 
 s += "gradience.addColorStop(1, '#000000');"; 
 s += "context.fillStyle = gradience;"; 
 s += " context.fill();"; 
 s += "context.closePath();"; 
 s += "context.restore();"; 
 s += "context.beginPath();"; 
 s += "context.strokeStyle = '#ffff00';"; 
 s += "context.translate(centerX,centerY);"; 
 s += "var increment = 5;"; 
   s += "context.font="15px Helvetica";"; 
s += "for (var i=-18; i<=18; i++)"; 
s += "{"; 
s += "angle = Math.PI/30*i;"; 
s += "sineAngle = Math.sin(angle);"; 
s += "cosAngle = -Math.cos(angle);"; 
s += "if (i % 5 == 0) {"; 
s += "context.lineWidth = 8;"; 
s += "iPointX = sineAngle *(radius -radius/4);"; 
s += "iPointY = cosAngle *(radius -radius/4);"; 
s += "oPointX = sineAngle *(radius -radius/7);"; 
s += "oPointY = cosAngle *(radius -radius/7);"; 
s += "wPointX = sineAngle *(radius -radius/2.5);"; 
s += "wPointY = cosAngle *(radius -radius/2.5);"; 
s += "context.fillText((i+18)*increment,wPointX-2,wPointY+4);"; 
s += "}"; 

t = "else";
t += "{";
t += "context.lineWidth = 2;";
t += "iPointX = sineAngle *(radius -radius/5.5);";
t += "iPointY = cosAngle *(radius -radius/5.5);";
t += "oPointX = sineAngle *(radius -radius/7);";
t += "oPointY = cosAngle *(radius -radius/7);";
t += "}";
t += "context.beginPath();";
t += "ontext.moveTo(iPointX,iPointY);";
t += "context.lineTo(oPointX,oPointY);";
t += "context.stroke()";
t += "context.closePath();";
t += "}";

u = "var numOfSegments = speed/increment;";
u += "numOfSegments = numOfSegments -18;";
u += "angle = Math.PI/30*numOfSegments;";
u += "sineAngle = Math.sin(angle);";
u += "cosAngle = -Math.cos(angle);";
u += "pointX = sineAngle *(3/4*radius);";
u += "pointY = cosAngle *(3/4*radius);";
u += "context.beginPath();";
u += "context.strokeStyle = '#000000';";
u += "context.arc(0, 0, 19, 0, 2*Math.PI, true);";
u += "context.fill();";
u += "context.closePath();";
u += "context.beginPath();";
u += "context.lineWidth=6;";
u += "context.moveTo(0,0);";
u += "context.lineTo(pointX,pointY);";
u += "context.stroke();";
u += "context.closePath();";
u += "context.restore();";
u += "context.translate(-centerX,-centerY);";
u += "}";

v = "</script>";
v += "</head>";
v += "<body onload="draw(19);">";
v += "<div>";
v += "Change the speed in the dropdown to see the dial position change";
v += "<select id="myList" onchange="redraw();">";
v += "<option value="120">Speed = 120</option>";
v += "<option value="30">Speed = 30</option>";
v += "<option value="50">Speed = 50</option>";
v += "<option value="60">Speed = 60</option>";
v += "<option value="140">Speed = 140</option>";
v += "<option value="160">Speed = 160</option>";
v += "<option value="160">Speed = 160</option>";
v += "</div>";
v += "<canvas class="canvas" id="myCanvas" width="600" height="600">";
v += "Your browser does not support the HTML5 canvas tag.</canvas>";
v += "</body>";
 v += "</html>";


 
  // Send the response to the client
  client.print(s+t+u+v);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}


