#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define RXD2 14
#define TXD2 12
#define BUTTON_PIN 0
#define LED_PIN 2

const char* ssid = "ESP8266_AP"; // SSID of the Access Point
const char* password = "12345678"; // Password for the Access Point
WiFiServer server(23);

SoftwareSerial mySerial(RXD2, TXD2);

#define TARGET_ID 2

String Message = "Hello from Dev1";
String content = "";
int counter = 0;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  delay(1000);

  // Initialize WiFi AP
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
  Serial.println("Telnet server started");

  // Initialize pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

void loop() {
  // Telnet server code
  if (!client || !client.connected()) {
    client = server.available();
  }

  if (client && client.connected()) {
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      client.print("You said: ");
      client.print(line);
      client.print("\r\n");
    }
  }

  // LoRa communication code
  if (Serial.available()) {
    String incoming = Serial.readString();
    client.println("Serial Writing: " + incoming);
    content = incoming;
    content.trim();
    content = content + "\r\n";
    char* bufc = (char*) malloc(sizeof(char) * (content.length() + 1));
    content.toCharArray(bufc, content.length() + 1);
    mySerial.write(bufc);
    free(bufc);
  }

  if (mySerial.available()) {
    String incoming = mySerial.readString();
    client.println("LoRa Received: " + incoming);
    if (incoming.length() <= 10) {
      Serial.println(incoming);
    } else {
      String channel_ID = incoming.substring(incoming.indexOf('=') + 1, incoming.indexOf(','));
      Serial.println("Channel ID : " + channel_ID);
      client.println("Channel ID : " + channel_ID);

      String str = incoming.substring(incoming.indexOf(',') + 1);

      String msgLength = str.substring(0, str.indexOf(','));
      Serial.println("Message Length : " + msgLength);
      client.println("Message Length : " + msgLength);

      String str2 = str.substring(str.indexOf(',') + 1);

      String message = str2.substring(0, str2.indexOf(','));
      Serial.println("Message : " + message);
      client.println("Message : " + message);

      String str3 = str2.substring(str2.indexOf(',') + 1);

      String rssi = str3.substring(0, str3.indexOf(','));
      Serial.println("RSSI : " + rssi);
      client.println("RSSI : " + rssi);

      String snr = str3.substring(str3.indexOf(',') + 1);

      Serial.println("SNR : " + snr);
      client.println("SNR : " + snr);
    }
  }

  // When the button is pressed send the message to other module
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(1000); // Debounce delay
    String data = Message + " - Count: " + counter;
    sendLoraData(data, TARGET_ID);
    // Increase counter on each send
    counter++;
    digitalWrite(LED_PIN, LOW);
    delay(500);
    digitalWrite(LED_PIN, HIGH);
  }
}

void sendLoraData(String data, int address) {
  String myString = "AT+SEND=" + String(address) + "," + String(data.length()) + "," + data + "\r\n";
  char* buf = (char*) malloc(sizeof(char) * (myString.length() + 1));
  Serial.println(myString);
  if (client && client.connected()) {
    client.println("Sending LoRa Data: " + myString);
  }
  myString.toCharArray(buf, myString.length() + 1);
  mySerial.write(buf);
  free(buf);
}



