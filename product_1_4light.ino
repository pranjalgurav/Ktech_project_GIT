    //Complete project details at https://randomnerdtutorials.com
//*********/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager

// Set web server port number to 80
WiFiServer server(80); 

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output1State = "off";
String output2State = "off";
String output5State = "off";
String output4State = "off";
// Assign output variables to GPIO pins
const int output1 = D1;
const int output2 = D2;
//const int output5 = D5;
//const int output4 = D6;
const int output5 = D7;
const int output4 = D8;

#define speaker D3
#define speed 
String valueString = String(0);
int positon1 = 0;
int positon2 = 0;


void setup() {
  Serial.begin(115200);
  // Serial.println(local_IP);
  // Initialize the output variables as outputs
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(speaker,OUTPUT);
  // Set outputs to LOW
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
analogWriteRange(100);
  
  WiFiManager wifiManager;
  
 
  wifiManager.autoConnect("KTECH");
 
  Serial.println("Connected.");

  server.begin();
}   

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {               
    digitalWrite(speaker,HIGH);
    delay(50);
    digitalWrite(speaker,LOW);// If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /1/on") >= 0)
            {
              Serial.println("GPIO 1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0)
            {
              Serial.println("GPIO 1 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) 
            {
              Serial.println("GPIO 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0)
            {
              Serial.println("GPIO 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }
             if (header.indexOf("GET /5/on") >= 0)
            {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0)
            {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) 
            {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0)
            {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");


            // Web Page Heading
            client.println("<body><h1>KTECH</h1>");
            //  client.println(WiFi.localIP());
            // Display current state, and ON/OFF buttons for GPIO 5

            ///////////////////////////////////////////////////////////////
            client.println("<p>GPIO 1 - State " + output1State + "</p>");
            // If the output5State is off, it displays the ON button
            if (output1State == "off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 4
            client.println("<p>GPIO 2 - State " + output2State + "</p>");
            // If the output4State is off, it displays the ON button
            if (output2State == "off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            /////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////
            client.println("<p>GPIO 5 - State " + output5State + "</p>");
            // If the output5State is off, it displays the ON button
            if (output5State == "off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 4
            client.println("<p>GPIO 4 - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button
            if (output4State == "off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            /////////////////////////////////////////////////////////////////////////////
//            // client.print("<input type=\"range\" min=\"0\" max=\"100\" value=\"0\" step=\"1\" onchange=\"showValue(this.value)\" /><br>");
//            //client.print("<span id=\"range\">0</span><br>");
//            //client.print("<script type=\"text/javascript\">function showValue(newValue){document.getElementById(\"range\").innerHTML=newValue;}</script>");
//            client.println("<p>Position: <span id=\"servoPos\"></span></p>");
//            client.println("<input type=\"range\" min=\"0\" max=\"100\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\"" + valueString + "\"/>");
//
//            client.println("<script>var slider = document.getElementById(\"servoSlider\");");
//            client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
//            client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
//            client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
//            client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        if(header.indexOf("GET /?value=")>=0) 
{
positon1 = header.indexOf('=');
positon2 = header.indexOf('&');
valueString = header.substring(positon1+1, positon2);

//Rotate the servo
//ObjServo.write(valueString.toInt());
Serial.println(valueString); 
analogWrite(D4,valueString.toInt());
delay(1);
} 
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
