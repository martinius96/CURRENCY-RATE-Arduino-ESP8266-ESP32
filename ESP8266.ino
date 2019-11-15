//Author: Bc. Martin Chlebovec (martinius96)
//E-mail: martinius96@gmail.com
//Website: https://arduino.php5.sk?lang=en
//PayPal: https://paypal.me/chlebovec
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char * ssid = "WIFI_SSID";
const char * password = "WIFI_PASS";
String apiKey = "ABCDEFGH12345678";
String currency = "EUR_CZK";

const char* host = "free.currconv.com";
const int httpsPort = 443; //http port
const char fingerprint[] PROGMEM = "‎97 73 f0 aa a6 80 bf cc 92 44 2a cf 0f fa 82 db 7a c8 45 8e";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi uspesne pripojene");
  Serial.println("IP adresa: ");
  Serial.println(WiFi.localIP());
  Serial.println("Ready");
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
  if (client.connect(host, httpsPort)) {
    String url = "/api/v7/convert?q=" + currency + "&compact=ultra&apiKey=" + apiKey;
    client.print(String("GET ") + url + " HTTP/1.0\r\n" + "Host: " + host + "\r\n" + "User-Agent: ESP8266\r\n" + "Connection: close\r\n\r\n");
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
      if (line == "\r") {
        break;
      }
    }
    String line = client.readStringUntil('\n');
    Serial.println(line);
    String abc = line.substring(11, 20);
    Serial.println("Kurz (orezany text): ");
    Serial.println(abc);
    float kurz = abc.toFloat();
    Serial.println("Kurz (float): ");
    Serial.println(kurz);
  }
}

void loop() {

}
