#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// ==== WiFi Credentials ====
const char* ssid = "Airtel_king_8747";
const char* password = "Kings@10";

// ==== Telegram Bot Info ====
String botToken = "8412873708:AAEMy3tNurddKOKwqZ_hGc5E0PE3chjMmKw";
String chatId   = "6367854937";

// ==== GPS + SOS Pin ====
HardwareSerial gpsSerial(1);  // UART1
TinyGPSPlus gps;
#define SOS_BUTTON 13

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 26, 27);  // GPS RX, TX
  pinMode(SOS_BUTTON, INPUT_PULLUP);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  while (gpsSerial.available() > 0) gps.encode(gpsSerial.read());

  if (digitalRead(SOS_BUTTON) == LOW) {
    Serial.println("SOS pressed!");
    if (gps.location.isValid()) sendTelegramAlert();
    else Serial.println("No GPS fix yet...");
    delay(5000);  // debounce / avoid multiple alerts
  }

  delay(100); // small delay for GPS parsing
}


void sendTelegramAlert() {
  if (!gps.location.isValid()) {
    Serial.println("No GPS fix yet...");
    return;
  }

  double lat = gps.location.lat();
  double lng = gps.location.lng();

  String message = "🚨 *SOS Alert!* 🚨\nLocation: https://maps.google.com/?q=" +
                   String(lat, 6) + "," + String(lng, 6);

  String url = "https://api.telegram.org/bot" + botToken +
               "/sendMessage?chat_id=" + chatId +
               "&text=" + urlencode(message) + "&parse_mode=Markdown";

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode == 200) Serial.println("Telegram Alert Sent!");
  else Serial.printf("Error sending alert: %d\n", httpCode);
  http.end();
}

// URL-encoder helper
String urlencode(String str) {
  String encoded = "";
  char c;
  char code0, code1;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (isalnum(c)) encoded += c;
    else if (c == ' ') encoded += '+';
    else {
      code1 = (c & 0xF) + '0';
      if ((c & 0xF) > 9) code1 = (c & 0xF) - 10 + 'A';
      code0 = ((c >> 4) & 0xF) + '0';
      if (((c >> 4) & 0xF) > 9) code0 = ((c >> 4) & 0xF) - 10 + 'A';
      encoded += '%';
      encoded += code0;
      encoded += code1;
    }
  }
  return encoded;
}
