/*
 *  This sketch sends data via HTTP GET requests to api.thingspeak.com, .
 *  which in turn makes a POST requst to the Twillio API sening the phone call or text message
 *  You need to get api_Key at api.thingspeak.com and paste it
 *  below. Or just customize this script to talk to other HTTP servers.
 *  code butchered by: JPellerin
 *  http://www.jpellerin.info/bl0g/
 */

#include <ESP8266WiFi.h>

// WiFi Creds
const char* ssid     = "<your_SSID>"; // replace <your_SSID> with your router name
const char* password = "<your_passwd>"; // Replace <your_passwd> with your network password

// ThingSpeak Creds
const char* host = "api.thingspeak.com";
const char* api_Key = "<your_api_key_goes_here>";

////////////////////////////////////////////////////////////////////
const int BUTTON = 0;/////// the input pin where the///////////////
const int LED = 2;      ///  the pin for the LED ///////////////// 
////////////////////////// pushbutton is connected///////////////
int val = 0;          /// val will be used to store the state///
//////////////////////// of the input pin//////////////////////
int old_val = 0;    /// stores the previous value of "val"////
int state = 0;//////// 0 = LED off while 1 = LED on//////////
unsigned long startTime = 0; // when did we begin pressing?/
///////////////////////////////////////////////////////////

void setup() {
  // Set BUTTON(GPIO0) as an input
  pinMode(BUTTON, INPUT);  
  // prepare GPIO2 as LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  
  Serial.begin(115200);
  delay(10);

  // Start by connecting to a WiFi network

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
  Serial.println("Aquired Teh WiFiz, time to Hack Planet!!");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

int value = 0;

void loop() { 
val = digitalRead(BUTTON); // read input value and store it
                            
 // check if there was a state transition
 if ((val == HIGH) && (old_val == LOW)){
   state = 1 - state;
   delay(10);
 }

 old_val = val; // val is now old, let's store it

 if (state == 1) {  // Sensor has changed the state, time to make 
                    // a GET request to the ThingSpeak API,
                    // which will POST to our Twillio account
                    //sending the call or message to our phone.
                    // Caution!!! making requests cost $ Use accordingly
   
   blink_1();
   alert();
   
   blink2();
   alert();
   
   blink2();
   strong();   

   blink2();
   
   Serial.print("connecting to ");
   Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/apps/thinghttp/";
  url += "send_request?api_key=";
  url += api_Key;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(1000);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
   state = 0;
 } else {
   allGood();   
 }

   deBug();  
  
  delay(1000); 

}









void blink_1() {
 digitalWrite(LED, HIGH); // turn LED ON
   delay(1000);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH); 
}

void blink2() {
    delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH);
   delay(100);
   digitalWrite(LED, LOW);
   delay(100);
   digitalWrite(LED, HIGH); 
}

void allGood() {
     digitalWrite(LED, LOW);
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("All Is G00d In 7he H00d!!!");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
}

void deBug() {
   Serial.print("VALUE IS: ");
  Serial.println(val);
  Serial.println("");
  Serial.println("");
   
  Serial.print("OLD VALUE IS: ");
  Serial.println(old_val);
  Serial.println("");
  Serial.println("");

  Serial.print("STATE IS: ");
  Serial.println(state);
  Serial.println(""); 
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println(""); 
}

void alert() {
   Serial.println("Intruder Alert!!!");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println(""); 
}

void strong() {
   Serial.println("Good thing your code hand is so strong!!!");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println("You should be getting a phone call or text message, careful they are not free!!!");
   Serial.println("");
   Serial.println("");
   Serial.println("");
   Serial.println(""); 
}
