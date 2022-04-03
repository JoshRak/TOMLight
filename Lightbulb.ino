#include <SPI.h> //What is used to communicate witht he WiFi chip
#include <WiFi101.h> //Wifi library fro Arduino MKR1000 and WiFi shield

int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;

char ssid[] = "test";      // your network SSID (name)
char pass[] = "bananaballs";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS; //status of wifi

WiFiServer server(80); //declare server object and spedify port, 80 is port used for internet

boolean flashing = false;
String currColor = "White";

void setup() {
  //Uncomment serial for debugging and to see details of WiFi connection
  RGB_color(255, 0, 0);
   Serial.begin(9600);
//  while (!Serial) {
//
//    ; // wait for serial port to connect. Needed for native USB port only
//
//  }
  Serial.println("Program started");
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  server.begin();

  RGB_color(255, 0, 0);
  delay(500);
  RGB_color(255, 255, 255);
}


void loop() {
  if (flashing){
    if (currColor == "Red"){
      RGB_color(255, 0, 0);
    }
    if (currColor == "Blue"){
      RGB_color(0, 0, 255);
    }
    if (currColor == "Green"){
      RGB_color(0, 255, 0);
    }
    if (currColor == "Cyan"){
      RGB_color(0, 255, 255);
    }
    if (currColor == "Magenta"){
      RGB_color(255, 0, 255);
    }
    if (currColor == "Yellow"){
      RGB_color(255, 255, 0);
    }
    if (currColor == "White"){
      RGB_color(255, 255, 255);
    }
    delay(250);
    RGB_color(0, 0, 0);
    delay(250);
  }
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,

 

    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then

 

        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Value at A0 is ");
            client.print(analogRead(A0));
            client.print("<br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        if (currentLine.endsWith("GET /Red")) {
          RGB_color(255, 0, 0);
          flashing = false;
        }
        if (currentLine.endsWith("GET /Green")) {
          RGB_color(0, 255, 0); 
          flashing = false;
        }
        if (currentLine.endsWith("GET /Blue")) {
          RGB_color(0, 0, 255);
          flashing = false; 
        }
        if (currentLine.endsWith("GET /Yellow")) {
          RGB_color(255, 255, 0); 
          flashing = false;
        }
        if (currentLine.endsWith("GET /Magenta")) {
          RGB_color(255, 0, 255); 
          flashing = false;
        }
        if (currentLine.endsWith("GET /Cyan")) {
          RGB_color(0, 255, 255); 
          flashing = false;
        }
        if (currentLine.endsWith("GET /White")) {
          RGB_color(255, 255, 255); 
          flashing = false;
        }

        if (currentLine.endsWith("GET /Red/Flashing")) {
          RGB_color(255, 0, 0);
          currColor = "Red";
          flashing = true;
        }
        if (currentLine.endsWith("GET /Green/Flashing")) {
          RGB_color(0, 255, 0); 
          currColor = "Green";
          flashing = true;
        }
        if (currentLine.endsWith("GET /Blue/Flashing")) {
          RGB_color(0, 0, 255); 
          currColor = "Blue";
          flashing = true;
        }
        if (currentLine.endsWith("GET /Yellow/Flashing")) {
          RGB_color(255, 255, 0); 
          currColor = "Yellow";
          flashing = true;
        }
        if (currentLine.endsWith("GET /Magenta/Flashing")) {
          RGB_color(255, 0, 255); 
          currColor = "Magenta";
          flashing = true;
        }
        if (currentLine.endsWith("GET /Cyan/Flashing")) {
          RGB_color(0, 255, 255); 
          currColor = "Cyan";
          flashing = true;
        }
        if (currentLine.endsWith("GET /White/Flashing")) {
          RGB_color(255, 255, 255); 
          currColor = "White";
          flashing = true;
        }

        if (currentLine.endsWith("GET /Red/Text")) {
          RGB_color(255, 0, 0);
          flashing = false;
          delay(5000);
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /Green/Text")) {
          RGB_color(0, 255, 0); 
          flashing = false;
          delay(5000);
          RGB_color(255, 255, 255);
        }
        
        if (currentLine.endsWith("GET /Blue/Text")) {
          RGB_color(0, 0, 255);
          flashing = false; 
          delay(5000);
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /Yellow/Text")) {
          RGB_color(255, 255, 0); 
          flashing = false;
          delay(5000);
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /Magenta/Text")) {
          RGB_color(255, 0, 255); 
          flashing = false;
          delay(5000);
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /Cyan/Text")) {
          RGB_color(0, 255, 255); 
          flashing = false;
          delay(5000);
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /White/Text")) {
          RGB_color(255, 255, 255); 
          flashing = false;
          delay(5000);
          RGB_color(255, 255, 255);
        }

        if (currentLine.endsWith("GET /Red/Flashing/Text")) {
          flashing = false;
          for (int i = 0; i<10; i++){
            RGB_color(255, 0, 0);
            delay(250);
            RGB_color(0, 0, 0);
            delay(250);
          }
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /Green/Flashing/Text")) {
          flashing = false;
          for (int i = 0; i<10; i++){
            RGB_color(0, 255, 0);
            delay(250);
            RGB_color(0, 0, 0);
            delay(250);
          }
          RGB_color(255, 255, 255);
        }
        
        if (currentLine.endsWith("GET /Blue/Flashing/Text")) {
          flashing = false;
          for (int i = 0; i<10; i++){
            RGB_color(0, 0, 255);
            delay(250);
            RGB_color(0, 0, 0);
            delay(250);
          }
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /Yellow/Flashing/Text")) {
          flashing = false;
          for (int i = 0; i<10; i++){
            RGB_color(255, 255, 0);
            delay(250);
            RGB_color(0, 0, 0);
            delay(250);
          }
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /Magenta/Flashing/Text")) {
          flashing = false;
          for (int i = 0; i<10; i++){
            RGB_color(255, 0, 255);
            delay(250);
            RGB_color(0, 0, 0);
            delay(250);
          }
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /Cyan/Flashing/Text")) {
          flashing = false;
          for (int i = 0; i<10; i++){
            RGB_color(0, 255, 255);
            delay(250);
            RGB_color(0, 0, 0);
            delay(250);
          }
          RGB_color(255, 255, 255);
        }
        if (currentLine.endsWith("GET /White/Flashing/Text")) {
          flashing = false;
          for (int i = 0; i<10; i++){
            RGB_color(255, 255, 255);
            delay(250);
            RGB_color(0, 0, 0);
            delay(250);
          }
          RGB_color(255, 255, 255);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
