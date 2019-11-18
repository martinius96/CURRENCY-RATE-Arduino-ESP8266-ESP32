//Author: Bc. Martin Chlebovec (martinius96)
//E-mail: martinius96@gmail.com
//Website: https://arduino.php5.sk?lang=en
//PayPal: https://paypal.me/chlebovec
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF }; //fyzicka adresa MAC
String apiKey = "ABCDEFGH12345678";
String currency = "EUR_CZK";
IPAddress ip(192, 168, 1, 100);

const char* host = "free.currconv.com";
const int httpPort = 80; //http port
EthernetClient client;
void setup() {
  Serial.begin(115200);
  if (Ethernet.begin(mac) == 0) {
    Ethernet.begin(mac, ip);
  }
  Serial.print("  DHCP nastavilo IP: ");
  Serial.println(Ethernet.localIP());
  Serial.println("Ready");
  if (client.connect(host, httpPort)) {
    String url = "/api/v7/convert?q=" + currency + "&compact=ultra&apiKey=" + apiKey;
    client.print(String("GET ") + url + " HTTP/1.0\r\n" + "Host: " + host + "\r\n" + "User-Agent: ArduinoEthernetW5100\r\n" + "Connection: close\r\n\r\n");
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
  client.stop();
}

void loop() {

}
